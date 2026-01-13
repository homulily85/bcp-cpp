//
// Created by homulily85 on 1/9/26.
//
#include "MaxSatSolver.h"

int SATSolver::MaxSatSolver::create_new_variable()
{
    return ++number_of_variables;
}

void SATSolver::MaxSatSolver::add_clause(const std::vector<int>& clause)
{
    clauses.push_back(clause);
}

void SATSolver::MaxSatSolver::add_clause(int l)
{
    clauses.push_back({l});
}

void SATSolver::MaxSatSolver::add_clause(int l1, int l2)
{
    if (l1 < l2)
    {
        clauses.push_back({l1, l2});
    }

    else
    {
        clauses.push_back({l2, l1});
    }
}

void SATSolver::MaxSatSolver::add_clause(int l1, int l2, int l3)
{
    const int x = std::min({l1, l2, l3});
    const int z = std::max({l1, l2, l3});
    const int y = l1 + l2 + l3 - x - z;

    clauses.push_back({x, y, z});
}

void SATSolver::MaxSatSolver::add_clause(int l1, int l2, int l3, int l4)
{
    clauses.push_back({l1, l2, l3, l4});
}

void SATSolver::MaxSatSolver::reset()
{
    number_of_variables = 0;
    clauses.clear();
    status = 0;
    time_accum = 0.0;
}

