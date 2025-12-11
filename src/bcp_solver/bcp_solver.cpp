//
// Created by homulily85 on 11/29/25.
//

#include "bcp_solver.h"

#include <queue>
#include <random>
#include <ranges>
#include <set>

void BCPSolver::BCPSolver::calculate_upper_bound()
{
    const int n = graph->get_number_of_nodes();

    std::vector colors(n, -1);

    std::vector<std::set<int>> neighbouring_colors(n);

    using Element = std::pair<int, int>;
    std::priority_queue<Element, std::vector<Element>, std::greater<>> saturations;

    int max_color = 0;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    if (const auto* edges = graph->get_edges())
    {
        for (const auto& edge : *edges)
        {
            int u = std::get<0>(edge);
            int v = std::get<1>(edge);
            int w = std::get<2>(edge);

            if (u >= 0 && u < n && v >= 0 && v < n)
            {
                adj[u].emplace_back(v, w);
                adj[v].emplace_back(u, w);
            }
        }
    }

    auto has_uncolored = [&]() -> bool
    {
        return std::any_of(colors.begin(), colors.end(), [](const int c) { return c == -1; });
    };

    auto get_start_node = [&]() -> int
    {
        int best_node = -1;
        int max_deg = -1;
        for (int i = 0; i < n; ++i)
        {
            if (colors[i] == -1)
            {
                if (const int deg = static_cast<int>(adj[i].size()); deg > max_deg)
                {
                    max_deg = deg;
                    best_node = i;
                }
            }
        }
        return best_node;
    };

    while (has_uncolored())
    {
        if (int start_node = get_start_node(); start_node != -1)
        {
            saturations.emplace(start_node, 0);
        }

        while (!saturations.empty())
        {
            std::pair<int, int> top = saturations.top();
            saturations.pop();
            int v = top.first;

            if (colors[v] > -1)
            {
                continue;
            }

            colors[v] = 0;

            std::vector<std::pair<int, int>> intervals;
            for (const auto& neighbor : adj[v])
            {
                int w = neighbor.first;
                int weight = neighbor.second;

                if (colors[w] > -1)
                {
                    intervals.emplace_back(colors[w] - weight, colors[w] + weight);
                }
            }

            std::sort(intervals.begin(), intervals.end());

            size_t invIndx = 0;
            while (invIndx < intervals.size() && colors[v] > intervals[invIndx].first)
            {
                colors[v] = std::max(colors[v], intervals[invIndx].second);
                invIndx++;
            }

            max_color = std::max(max_color, colors[v]);

            for (const auto& key : adj[v] | std::views::keys)
            {
                if (int w = key; colors[w] == -1)
                {
                    neighbouring_colors[w].insert(v);
                    saturations.emplace(w, static_cast<int>(neighbouring_colors[w].size()));
                }
            }
        }
    }

    upper_bound = max_color;
}

void BCPSolver::BCPSolver::create_variable()
{
    delete x;
    delete y;

    if (method == TwoVariablesGreater || method == TwoVariablesLess)
    {
        x = new std::map<std::pair<int, int>, int>();
    }

    y = new std::map<std::pair<int, int>, int>();

    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span + 1; c++)
        {
            if (method == TwoVariablesGreater || method == TwoVariablesLess)
            {
                x->insert(std::pair<std::pair<int, int>, int>({i, c}, sat_solver->create_new_variable()));
            }
            y->insert(std::pair<std::pair<int, int>, int>({i, c}, sat_solver->create_new_variable()));
        }
    }
}

void BCPSolver::BCPSolver::encode()
{
    const auto start_time = std::chrono::high_resolution_clock::now();

    create_variable();

    symmetry_breaking();

    switch (method)
    {
    case TwoVariablesGreater:
        two_variables_greater_first_constraint();
        two_variables_greater_second_constraint();
        two_variables_greater_third_constraint();
        two_variables_greater_fourth_constraint();
        break;

    case TwoVariablesLess:
        two_variables_less_first_constraint();
        two_variables_less_second_constraint();
        two_variables_less_third_constraint();
        two_variables_less_fourth_constraint();
        break;

    case OneVariableGreater:
        one_variable_greater_first_constraint();
        one_variable_greater_second_constraint();
        one_variable_greater_third_constraint();
        break;

    case OneVariableLess:
        one_variable_less_first_constraint();
        one_variable_less_second_constraint();
        one_variable_less_third_constraint();
        break;

    default:
        throw std::invalid_argument("Invalid solving method");
    }

    encoding_time += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
}

void BCPSolver::BCPSolver::one_variable_greater_first_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        sat_solver->add_clause((*y)[{i, 1}]);
    }
}

void BCPSolver::BCPSolver::one_variable_greater_second_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 2; c < span + 1; c++)
        {
            sat_solver->add_clause(-(*y)[{i, c}], (*y)[{i, c - 1}]);
        }
    }
}

void BCPSolver::BCPSolver::one_variable_greater_third_constraint() const
{
    for (const auto& edge : *graph->get_edges())
    {
        auto [u, v, weight] = edge;
        for (int c = 1; c <= span; c++)
        {
            if (c - weight < 0 && c + weight > span)
            {
                if (c == span)
                {
                    sat_solver->add_clause(-(*y)[{u, c}]);
                }
                else
                {
                    sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c + 1}]);
                }
            }
            else if (c - weight < 0)
            {
                sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c + 1}], (*y)[{v, c + weight}]);
            }
            else if (c + weight > span)
            {
                if (c == span)
                {
                    sat_solver->add_clause(-(*y)[{u, c}], -(*y)[{v, c - weight + 1}]);
                }
                else
                {
                    sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c + 1}], -(*y)[{v, c - weight + 1}]);
                }
            }
            else
            {
                sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c + 1}], (*y)[{v, c + weight}],
                                       -(*y)[{v, c - weight + 1}]);
            }
        }
    }
}

void BCPSolver::BCPSolver::one_variable_less_first_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        sat_solver->add_clause((*y)[{i, span}]);
    }
}

void BCPSolver::BCPSolver::one_variable_less_second_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span; c++)
        {
            sat_solver->add_clause(-(*y)[{i, c}], (*y)[{i, c + 1}]);
        }
    }
}

void BCPSolver::BCPSolver::one_variable_less_third_constraint() const
{
    for (const auto& edge : *graph->get_edges())
    {
        auto [u, v, weight] = edge;

        for (int c = 1; c <= span; c++)
        {
            if (c - weight < 1 && c + weight - 1 > span)
            {
                sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c - 1}]);
            }
            else if (c - weight < 1)
            {
                if (c == 1)
                {
                    sat_solver->add_clause(-(*y)[{u, c}], -(*y)[{v, c + weight - 1}]);
                }
                else
                {
                    sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c - 1}], -(*y)[{v, c + weight - 1}]);
                }
            }
            else if (c + weight - 1 > span)
            {
                if (c == 1)
                {
                    sat_solver->add_clause(-(*y)[{u, c}]);
                }
                else
                {
                    sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c - 1}], (*y)[{v, c - weight}]);
                }
            }
            else
            {
                sat_solver->add_clause(-(*y)[{u, c}], (*y)[{u, c - 1}], -(*y)[{v, c + weight - 1}],
                                       (*y)[{v, c - weight}]);
            }
        }
    }
}

void BCPSolver::BCPSolver::two_variables_greater_first_constraint() const
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

void BCPSolver::BCPSolver::two_variables_greater_second_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        sat_solver->add_clause((*y)[{i, 1}]);
    }
}

void BCPSolver::BCPSolver::two_variables_greater_third_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 2; c < span + 1; c++)
        {
            sat_solver->add_clause(-(*y)[{i, c}], (*y)[{i, c - 1}]);
        }
    }
}

void BCPSolver::BCPSolver::two_variables_greater_fourth_constraint() const
{
    for (const auto& edge : *graph->get_edges())
    {
        if (auto [u, v, weight] = edge; weight == 1)
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - 1 < 0 && c + 1 > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else
                {
                    sat_solver->add_clause(-(*x)[{u, c}], -(*x)[{v, c}]);
                }
            }
        }
        else
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - weight < 0 && c + weight > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else if (c - weight < 0)
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

void BCPSolver::BCPSolver::two_variables_less_first_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span + 1; c++)
        {
            if (c == 1)
            {
                sat_solver->add_clause(-(*x)[{i, c}], (*y)[{i, c}]);
                sat_solver->add_clause((*x)[{i, c}], -(*y)[{i, c}]);
            }
            else
            {
                sat_solver->add_clause(-(*x)[{i, c}], (*y)[{i, c}]);
                sat_solver->add_clause(-(*x)[{i, c}], -(*y)[{i, c - 1}]);
                sat_solver->add_clause((*x)[{i, c}], -(*y)[{i, c}], (*y)[{i, c - 1}]);
            }
        }
    }
}

void BCPSolver::BCPSolver::two_variables_less_second_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        sat_solver->add_clause((*y)[{i, span}]);
    }
}

void BCPSolver::BCPSolver::two_variables_less_third_constraint() const
{
    for (int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        for (int c = 1; c < span; c++)
        {
            sat_solver->add_clause(-(*y)[{i, c}], (*y)[{i, c + 1}]);
        }
    }
}

void BCPSolver::BCPSolver::two_variables_less_fourth_constraint() const
{
    for (const auto& edge : *graph->get_edges())
    {
        if (auto [u, v, weight] = edge; weight == 1)
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - 1 < 0 && c + 1 > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else
                {
                    sat_solver->add_clause(-(*x)[{u, c}], -(*x)[{v, c}]);
                }
            }
        }
        else
        {
            for (int c = 1; c <= span; c++)
            {
                if (c - weight < 1 && c + weight - 1 > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}]);
                }
                else if (c - weight < 1)
                {
                    sat_solver->add_clause(-(*x)[{u, c}], -(*y)[{v, c + weight - 1}]);
                }
                else if (c + weight - 1 > span)
                {
                    sat_solver->add_clause(-(*x)[{u, c}], (*y)[{v, c - weight}]);
                }
                else
                {
                    sat_solver->add_clause(-(*x)[{u, c}], -(*y)[{v, c + weight - 1}], (*y)[{v, c - weight}]);
                }
            }
        }
    }
}

void BCPSolver::BCPSolver::symmetry_breaking() const
{
    if (method == TwoVariablesGreater || method == OneVariableGreater)
    {
        sat_solver->add_clause(-(*y)[{graph->get_highest_degree_vertex(), span / 2 + 1}]);
    }
    else if (method == TwoVariablesLess || method == OneVariableLess)
    {
        sat_solver->add_clause((*y)[{graph->get_highest_degree_vertex(), span / 2 + 1}]);
    }
}

BCPSolver::BCPSolver::BCPSolver(const SolvingMethod method, const Graph* graph, const int upper_bound)
    : graph(graph), upper_bound(upper_bound), method(method)
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

BCPSolver::SolverStatus BCPSolver::BCPSolver::non_optimal_solving(const double time_limit)
{
    encode();
    if (const int result = sat_solver->solve(nullptr, time_limit); result == CaDiCaL::Status::UNKNOWN)
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

BCPSolver::SolverStatus BCPSolver::BCPSolver::optimal_solving_non_incremental(const double time_limit)
{
    int result{non_optimal_solving(time_limit)};

    if (result == UNKNOWN)
    {
        status = UNKNOWN;
        return status;
    }

    if (result == UNSATISFIABLE)
    {
        status = UNSATISFIABLE;
        return status;
    }

    while (result == SATISFIABLE || result == CaDiCaL::Status::SATISFIABLE && span > lower_bound)
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
            const auto remaining_time = time_limit - encoding_time - sat_solver->get_statistics()["total_solving_time"];
            result = sat_solver->solve(nullptr, remaining_time);

            if (result != CaDiCaL::Status::SATISFIABLE)
            {
                span++;
            }
        }
    }

    status = result != CaDiCaL::Status::UNKNOWN ? OPTIMAL : SATISFIABLE;
    return status;
}

BCPSolver::SolverStatus BCPSolver::BCPSolver::optimal_solving_incremental(const double time_limit)
{
    int result{non_optimal_solving(time_limit)};

    if (result == UNKNOWN)
    {
        status = UNKNOWN;
        return status;
    }

    if (result == UNSATISFIABLE)
    {
        status = UNSATISFIABLE;
        return status;
    }

    while (result == SATISFIABLE || result == CaDiCaL::Status::SATISFIABLE && span > lower_bound)
    {
        auto* assumptions{new std::vector<int>(graph->get_number_of_nodes())};

        if (method == TwoVariablesGreater || method == OneVariableGreater)
        {
            for (int i = 0; i < graph->get_number_of_nodes(); i++)
            {
                (*assumptions)[i] = -(*y)[{i, span}];
            }
        }

        else if (method == TwoVariablesLess || method == OneVariableLess)
        {
            for (int i = 0; i < graph->get_number_of_nodes(); i++)
            {
                (*assumptions)[i] = (*y)[{i, span - 1}];
            }
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
            const auto remaining_time = time_limit - encoding_time - sat_solver->get_statistics()["total_solving_time"];
            result = sat_solver->solve(assumptions, remaining_time);

            if (result == CaDiCaL::Status::SATISFIABLE)
            {
                span--;
            }
        }
        delete assumptions;
    }

    status = result != CaDiCaL::Status::UNKNOWN ? OPTIMAL : SATISFIABLE;
    return status;
}

BCPSolver::SolverStatus BCPSolver::BCPSolver::solve(const double time_limit, const bool find_optimal,
                                                    const bool incremental)
{
    if (!find_optimal)
    {
        return non_optimal_solving(time_limit);
    }
    else
    {
        if (!incremental)
        {
            return optimal_solving_non_incremental(time_limit);
        }

        else
        {
            return optimal_solving_incremental(time_limit);
        }
    }
}

int BCPSolver::BCPSolver::get_span() const
{
    return (status != UNKNOWN && status != UNSATISFIABLE) ? span : -1;
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
