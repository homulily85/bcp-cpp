//
// Created by homulily85 on 11/29/25.
//

#include "SatSolver.h"

#include "card_encoder/clset.hh"
#include "card_encoder/seqcounter.hh"

int SATSolver::SatSolver::create_new_variable()
{
    number_of_variables++;
    return number_of_variables;
}

std::unordered_map<std::string, double> SATSolver::SatSolver::get_statistics() const
{
    auto stats = std::unordered_map<std::string, double>();
    stats["total_solving_time"] = time_accum;
    stats["clauses"] = number_of_clauses;
    stats["variables"] = number_of_variables;
    return stats;
}

// void SATSolver::SatSolver::encode_equals_k(const std::vector<int>& vars, int k)
// {
//     auto clauseSet = ClauseSet();
//     seqcounter_encode_atmostN(number_of_variables, clauseSet, const_cast<std::vector<int>&>(vars), k);
//
//     int new_variable_max_index = -1;
//
//     for (const auto& clause : clauseSet.get_clauses())
//     {
//         for (const auto lit : clause)
//         {
//             if (const int var_index = std::abs(lit); var_index > new_variable_max_index)
//             {
//                 new_variable_max_index = var_index;
//             }
//         }
//     }
//
//     number_of_variables = std::max(number_of_variables, new_variable_max_index);
//
//     new_variable_max_index = -1;
//     seqcounter_encode_atleastN(number_of_variables, clauseSet, const_cast<std::vector<int>&>(vars), k);
//     for (const auto& clause : clauseSet.get_clauses())
//     {
//         add_clause(clause);
//         for (const auto lit : clause)
//         {
//             if (const int var_index = std::abs(lit); var_index > new_variable_max_index)
//             {
//                 new_variable_max_index = var_index;
//             }
//         }
//     }
//     number_of_variables = std::max(number_of_variables, new_variable_max_index);
// }

void SATSolver::SatSolver::encode_equals_k(const std::vector<int>& vars, int k)
{
    auto clauseSet = ClauseSet();

    seqcounter_encode_atmostN(number_of_variables, clauseSet, const_cast<std::vector<int>&>(vars), k);

    int current_max_var = number_of_variables;
    auto& pb_clauses = clauseSet.get_clauses();

    size_t processed_count = 0;
    for (auto& clause : pb_clauses)
    {
        ranges::sort(clause);
        add_clause(clause);

        for (const auto lit : clause)
        {
            if (const int var_index = std::abs(lit); var_index > current_max_var) current_max_var = var_index;
        }
        processed_count++;
    }

    number_of_variables = current_max_var;

    seqcounter_encode_atleastN(number_of_variables, clauseSet, const_cast<std::vector<int>&>(vars), k);

    auto& all_clauses = clauseSet.get_clauses();
    for (size_t i = processed_count; i < all_clauses.size(); ++i)
    {
        auto& clause = all_clauses[i];
        ranges::sort(clause);
        add_clause(clause);

        for (const auto lit : clause)
        {
            if (const int var_index = std::abs(lit); var_index > current_max_var) current_max_var = var_index;
        }
    }

    number_of_variables = current_max_var;
}