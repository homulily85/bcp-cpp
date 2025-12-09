//
// Created by homulily85 on 11/29/25.
//

#include "bcp_solver.h"

#include <iostream>
void BCPSolver::BCPSolver::calculate_upper_bound()
{
    const int n = graph->get_number_of_nodes();
    auto *assigned_colors = new std::vector(n, 0);

    for (int i = 0; i < n; ++i)
    {

        int candidate_color = 1;

        while (true)
        {
            bool violated = false;

            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                    continue;

                if (assigned_colors->at(j) != 0)
                {
                    int w = graph->get_weight(i, j);
                    if (w > 0)
                    {
                        if (std::abs(candidate_color - assigned_colors->at(j)) < w)
                        {
                            candidate_color++;
                            violated = true;
                            break;
                        }
                    }
                }
            }

            if (!violated)
            {
                break;
            }
        }

        assigned_colors->at(i) = candidate_color;
        if (candidate_color > upper_bound)
        {
            upper_bound = candidate_color;
        }
    }
    delete assigned_colors;
}

void BCPSolver::BCPSolver::first_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span + 1; c++)
        {
            if (c == span)
            {
                sat_solver->add_clause(-(*x)[{i, c}], (*y)[{i, c}]);
                sat_solver->add_clause((*x)[{i, c}], -(*y)[{i, c}]);
            }
            else
            {
                sat_solver->add_clause(-(*x)[{i, c}], (*y)[{i, c}]);
                sat_solver->add_clause(-(*x)[{i, c}], -(*y)[{i, c + 1}]);
                sat_solver->add_clause((*x)[{i, c}], -(*y)[{i, c}], (*y)[{i, c + 1}]);
            }
        }
    }
}

void BCPSolver::BCPSolver::second_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        sat_solver->add_clause((*y)[{i, 1}]);
    }
}

void BCPSolver::BCPSolver::third_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 2; c < span + 1; c++)
        {
            sat_solver->add_clause(-(*y)[{i, c}], (*y)[{i, c - 1}]);
        }
    }
}

void BCPSolver::BCPSolver::fourth_constraint() const
{
    for (const auto &edge : *graph->get_edges())
    {

        if (auto [u, v, weight] = edge; weight <= 1)
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - weight < 0 && c + weight > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else
                {
                    for (int j = c - weight + 1; j < c + weight; j++)
                    {
                        if (j > 0 && j <= span)
                        {
                            sat_solver->add_clause(-(*x)[{u, c}], -(*x)[{v, j}]);
                        }
                    }
                }
            }
        }
        else
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - weight + 1 < 1 && c + weight > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else if (c - weight + 1 < 1)
                {
                    sat_solver->add_clause(-(*x)[{u, c}], (*y)[{v, c + weight}]);
                }
                else if (c + weight > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}], -(*y)[{v, c - weight + 1}]);
                }
                else
                {
                    sat_solver->add_clause(-(*x)[{u, c}], (*y)[{v, c + weight}], -(*y)[{v, c - weight + 1}]);
                }
            }
        }
    }
}
void BCPSolver::BCPSolver::symmetry_breaking() const
{
    // sat_solver->add_clause(-(*y)[{1, span / 2 + 1}]);
    sat_solver->add_clause(-(*y)[{graph->get_highest_degree_vertex(), span / 2 + 1}]);
}

BCPSolver::BCPSolver::BCPSolver(const Graph *graph, const int upper_bound) : graph(graph), upper_bound(upper_bound)
{
    if (this->upper_bound < 0)
    {
        calculate_upper_bound();
    }

    span = this->upper_bound;
}

BCPSolver::BCPSolver::~BCPSolver()
{
    delete sat_solver;
    delete x;
    delete y;
}

BCPSolver::SOLVER_STATUS BCPSolver::BCPSolver::solve(const double time_limit, bool find_optimal, bool incremental)
{
    encode();

    int result;

    if (!find_optimal)
    {
        result = sat_solver->solve(nullptr, time_limit);
        if (result == CaDiCaL::Status::UNKNOWN)
        {
            status = UNKNOWN;
            return status;
        }
        else
        {
            status = result == CaDiCaL::Status::SATISFIABLE ? SATISFIABLE : UNSATISFIABLE;
            return status;
        }
    }
    else
    {
        result =
            time_limit != NO_TIME_LIMIT ? sat_solver->solve(nullptr, time_limit - encoding_time) : sat_solver->solve();
        if (result == CaDiCaL::Status::UNKNOWN)
        {
            status = UNKNOWN;
            return status;
        }
        if (result == CaDiCaL::Status::UNSATISFIABLE)
        {
            status = UNSATISFIABLE;
            return status;
        }

        while (result == CaDiCaL::Status::SATISFIABLE && span > 1)
        {
            if (!incremental)
            {
                sat_solver->reset();
                span--;
                encode();

                if (time_limit == NO_TIME_LIMIT)
                {
                    result = sat_solver->solve();
                    if (result != CaDiCaL::Status::SATISFIABLE)
                    {
                        span++;
                    }
                }
                else
                {
                    const auto remaining_time =
                        time_limit - encoding_time - sat_solver->get_statistics()["total_solving_time"];
                    result = sat_solver->solve(nullptr, remaining_time);

                    if (result != CaDiCaL::Status::SATISFIABLE)
                    {
                        span++;
                    }
                }
            }
            else
            {
                auto *assumptions = new std::vector<int>(graph->get_number_of_nodes());

                for (int i = 0; i < graph->get_number_of_nodes(); i++)
                {
                    (*assumptions)[i] = -(*y)[{i, span}];
                }
                if (time_limit == NO_TIME_LIMIT)
                {
                    result = sat_solver->solve(assumptions);
                    if (result == CaDiCaL::Status::SATISFIABLE)
                    {
                        span--;
                    }
                }
                else
                {
                    const auto remaining_time =
                        time_limit - encoding_time - sat_solver->get_statistics()["total_solving_time"];
                    result = sat_solver->solve(assumptions, remaining_time);

                    if (result == CaDiCaL::Status::SATISFIABLE)
                    {
                        span--;
                    }
                }
                delete assumptions;
            }
        }
    }
    status = result != CaDiCaL::Status::UNKNOWN ? OPTIMAL : SATISFIABLE;
    return status;
}

std::unordered_map<std::string, double> BCPSolver::BCPSolver::get_statistics() const
{
    auto stats = std::unordered_map<std::string, double>();
    auto sat_solver_stats = sat_solver->get_statistics();
    stats["V"] = graph->get_number_of_nodes();
    stats["E"] = graph->get_number_of_edges();
    stats["upper_bound"] = upper_bound;
    stats["variables"] = sat_solver_stats["variables"];
    stats["clauses"] = sat_solver_stats["clauses"];
    stats["status"] = status;
    stats["span"] = get_span();
    stats["encoding_time"] = encoding_time;
    stats["total_solving_time"] = sat_solver_stats["total_solving_time"];
    stats["time_used"] = encoding_time + sat_solver_stats["total_solving_time"];

    return stats;
}

void BCPSolver::BCPSolver::create_variable()
{
    delete x;
    delete y;

    x = new std::map<std::pair<int, int>, int>();
    y = new std::map<std::pair<int, int>, int>();

    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span + 1; c++)
        {
            x->insert(std::pair<std::pair<int, int>, int>({i, c}, sat_solver->create_new_variable()));
            y->insert(std::pair<std::pair<int, int>, int>({i, c}, sat_solver->create_new_variable()));
        }
    }

    // for (int i = 0; i < graph->get_number_of_nodes(); i++)
    // {
    //     for (int c = 1; c < span + 1; c++)
    //     {
    //         y->insert(std::pair<std::pair<int, int>, int>({i, c}, sat_solver->create_new_variable()));
    //     }
    // }
}

void BCPSolver::BCPSolver::encode()
{
    const auto start_time = std::chrono::high_resolution_clock::now();

    create_variable();

    symmetry_breaking();
    first_constraint();
    second_constraint();
    third_constraint();
    fourth_constraint();

    encoding_time += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
}
