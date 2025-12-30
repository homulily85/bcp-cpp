//
// Created by homulily85 on 11/29/25.
//

#include "SatSolver.h"

#include <condition_variable>
#include <thread>

#include "card_encoder/clset.hh"
#include "card_encoder/seqcounter.hh"

SATSolver::SatSolver::~SatSolver()
{
    delete solver;
}

int SATSolver::SatSolver::create_new_variable()
{
    number_of_variables++;
    return number_of_variables;
}

void SATSolver::SatSolver::add_clause(const std::vector<int>& clause)
{
    number_of_clauses++;
    solver->clause(clause);
}

void SATSolver::SatSolver::add_clause(const int l)
{
    number_of_clauses++;
    solver->clause(l);
    // std::cout << '[' << l << ']' << '\n';
}

void SATSolver::SatSolver::add_clause(const int l1, const int l2)
{
    number_of_clauses++;
    if (l1 < l2)
    {
        solver->clause(l1, l2);
    }

    else
    {
        solver->clause(l2, l1);
    }
    // std::cout << '[' << l1 << ", " << l2 << ']' << '\n';
}

void SATSolver::SatSolver::add_clause(const int l1, const int l2, const int l3)
{
    number_of_clauses++;
    int x = std::min({l1, l2, l3});
    int z = std::max({l1, l2, l3});
    int y = l1 + l2 + l3 - x - z;
    solver->clause(x, y, z);
    // std::cout << '[' << l1 << ", " << l2 << ", " << l3 << ']' << '\n';
}

void SATSolver::SatSolver::add_clause(const int l1, const int l2, const int l3, const int l4)
{
    number_of_clauses++;
    solver->clause(l1, l2, l3, l4);
    // std::cout << '[' << l1 << ", " << l2 << ", " << l3 << ", " << l4 << ']' << '\n';
}

int SATSolver::SatSolver::solve(const std::vector<int>* assumptions, const double time_limit)
{
    if (time_limit != NO_TIME_LIMIT && time_limit < 0.0)
    {
        // Time limit already exceeded before we started
        status = CaDiCaL::Status::UNKNOWN;
        return status;
    }

    if (assumptions != nullptr)
    {
        for (const auto assumption : *assumptions)
        {
            solver->assume(assumption);
        }
    }

    const auto start_time = std::chrono::high_resolution_clock::now();

    if (time_limit == NO_TIME_LIMIT)
    {
        status = solver->solve();
    }
    else
    {
        // 1. Create the terminator on the stack (it must outlive the thread usage)
        AtomicTerminator terminator;
        solver->connect_terminator(&terminator);

        // 2. Synchronization primitives
        std::mutex mtx;
        std::condition_variable cv;
        bool finished = false; // Flag to tell timer thread we are done

        // 3. Start the timer thread
        std::thread timer_thread([&]()
        {
            std::unique_lock<std::mutex> lk(mtx);
            // Wait for 'time_limit' OR until 'finished' becomes true.
            // wait_for returns false if it timed out.
            if (!cv.wait_for(lk, std::chrono::duration<double>(time_limit), [&] { return finished; }))
            {
                // If we are here, it means we timed out. Signal termination.
                terminator.force_terminate.store(true, std::memory_order_relaxed);
            }
        });

        // 4. Run the solver (Main Thread)
        status = solver->solve();

        // 5. Signal the timer thread that we finished
        {
            std::lock_guard<std::mutex> lk(mtx);
            finished = true;
        }
        cv.notify_one(); // Wake up the timer thread if it's sleeping

        // 6. Safely join the thread.
        // Because of the notification, the thread will wake up and exit immediately
        // if the solver finished early.
        if (timer_thread.joinable())
        {
            timer_thread.join();
        }

        solver->disconnect_terminator();
    }

    time_accum += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();

    return status;
}

std::unordered_map<std::string, double> SATSolver::SatSolver::get_statistics() const
{
    auto stats = std::unordered_map<std::string, double>();
    stats["total_solving_time"] = time_accum;
    stats["clauses"] = number_of_clauses;
    // stats["variables"] = solver->vars();
    stats["variables"] = number_of_variables;
    return stats;
}

void SATSolver::SatSolver::reset()
{
    number_of_clauses = 0;
    number_of_variables = 0;
    delete solver;
    solver = new CaDiCaL::Solver();
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
    auto& clauses = clauseSet.get_clauses();

    size_t processed_count = 0;
    for (auto& clause : clauses)
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