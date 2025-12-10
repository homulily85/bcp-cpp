//
// Created by homulily85 on 11/29/25.
//

#include "bcp_solver.h"

#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>

void BCPSolver::BCPSolver::bron_kerbosch(const std::vector<int> &R, std::vector<int> P, std::vector<int> X,
                                         const std::vector<std::vector<bool>> &adj,
                                         const std::vector<std::vector<int>> &weights, const long long m,
                                         std::vector<int> &best_clique, long long &max_score)
{
    if (P.empty() && X.empty())
    {
        if (R.empty())
            return;

        const long long cut = calculate_cut_size(R, static_cast<int>(adj.size()), weights);

        if (const long long score = static_cast<long long>(R.size()) * m + cut; score > max_score)
        {
            max_score = score;
            best_clique = R;
        }
        return;
    }

    int pivot = -1;
    if (!P.empty())
        pivot = P[0];
    else if (!X.empty())
        pivot = X[0];

    for (std::vector<int> P_copy = P; int v : P_copy)
    {
        if (pivot != -1 && adj[pivot][v])
        {
            continue;
        }

        std::vector<int> new_R = R;
        new_R.push_back(v);

        std::vector<int> new_P;
        std::vector<int> new_X;

        for (int p_node : P)
        {
            if (adj[v][p_node])
                new_P.push_back(p_node);
        }

        for (int x_node : X)
        {
            if (adj[v][x_node])
                new_X.push_back(x_node);
        }

        bron_kerbosch(new_R, new_P, new_X, adj, weights, m, best_clique, max_score);

        if (auto it_p = std::ranges::find(P, v); it_p != P.end())
            P.erase(it_p);
        X.push_back(v);
    }
}

long long BCPSolver::BCPSolver::calculate_cut_size(const std::vector<int> &clique, const int n,
                                                   const std::vector<std::vector<int>> &weights)
{
    long long cut = 0;
    std::vector in_clique(n, false);
    for (const int node : clique)
    {
        in_clique[node] = true;
    }

    for (const int u : clique)
    {
        for (int v = 0; v < n; ++v)
        {
            if (!in_clique[v] && weights[u][v] > 0)
            {
                cut += weights[u][v];
            }
        }
    }
    return cut;
}

void BCPSolver::BCPSolver::calculate_upper_bound()
{
    const int n = graph->get_number_of_nodes();

    std::vector colors(n, -1);

    std::vector<std::set<int>> neighbouring_colors(n);

    using Element = std::pair<int, int>;
    std::priority_queue<Element, std::vector<Element>, std::greater<>> saturations;

    int max_color = 0;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    if (const auto *edges = graph->get_edges())
    {
        for (const auto &edge : *edges)
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

    auto has_uncolored = [&]() -> bool {
        return std::any_of(colors.begin(), colors.end(), [](int c) { return c == -1; });
    };

    auto get_start_node = [&]() -> int {
        int best_node = -1;
        int max_deg = -1;
        for (int i = 0; i < n; ++i)
        {
            if (colors[i] == -1)
            {
                int deg = static_cast<int>(adj[i].size());
                if (deg > max_deg)
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
        int start_node = get_start_node();
        if (start_node != -1)
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
            for (const auto &neighbor : adj[v])
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

            for (const auto &key : adj[v] | std::views::keys)
            {
                int w = key;
                if (colors[w] == -1)
                {
                    neighbouring_colors[w].insert(v);
                    saturations.emplace(w, static_cast<int>(neighbouring_colors[w].size()));
                }
            }
        }
    }

    upper_bound = max_color;
}
void BCPSolver::BCPSolver::calculate_lower_bound()
{
    const int n = graph->get_number_of_nodes();
    const int m = graph->get_number_of_edges();

    std::vector adj(n, std::vector(n, false));
    std::vector weights(n, std::vector(n, 0));

    if (const auto *edges = graph->get_edges())
    {
        for (const auto &edge : *edges)
        {
            int u = std::get<0>(edge);
            int v = std::get<1>(edge);
            int w = std::get<2>(edge);
            if (u >= 0 && u < n && v >= 0 && v < n)
            {
                adj[u][v] = adj[v][u] = true;
                weights[u][v] = weights[v][u] = w;
            }
        }
    }

    std::vector<int> max_clique_rep;
    long long clique_val_rep = -1;

    if (const double density = (n > 1) ? (2.0 * m) / (static_cast<double>(n) * n - n) : 0.0; density <= 0.2 && n < 200)
    {
        std::vector<int> R;
        std::vector<int> P(n);
        std::iota(P.begin(), P.end(), 0); // Fill 0 to n-1
        std::vector<int> X;

        bron_kerbosch(R, P, X, adj, weights, m, max_clique_rep, clique_val_rep);
    }
    // --- BRANCH 2: Heuristic (Maximal Independent Set on Complement) ---
    else
    {
        // Finding MIS on Complement is equivalent to finding Maximal Clique on G.
        // Logic: Shuffle nodes, greedily build clique by keeping only valid neighbors.

        auto start_time = std::chrono::steady_clock::now();
        int iterations = 300 * (n > 0 ? static_cast<int>(std::round(static_cast<double>(m) / n)) : 1);
        if (iterations == 0)
            iterations = 1;

        std::vector<int> nodes(n);
        std::iota(nodes.begin(), nodes.end(), 0);

        for (int i = 0; i < iterations; ++i)
        {
            // Check time limit (100 seconds)
            auto current_time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() > 100)
            {
                break;
            }

            // Shuffle nodes (mimicking seed=i)
            std::mt19937 g(i);
            std::shuffle(nodes.begin(), nodes.end(), g);

            // Greedy Maximal Clique Construction
            std::vector<int> clique;
            if (!nodes.empty())
            {
                // Start with first node in shuffled list
                clique.push_back(nodes[0]);

                // Keep track of candidates: nodes connected to ALL nodes in current clique
                // Optimization: Just check against current clique members
                for (size_t k = 1; k < nodes.size(); ++k)
                {
                    int candidate = nodes[k];
                    bool connected_to_all = true;
                    for (const int member : clique)
                    {
                        if (!adj[candidate][member])
                        {
                            connected_to_all = false;
                            break;
                        }
                    }
                    if (connected_to_all)
                    {
                        clique.push_back(candidate);
                    }
                }
            }

            // Calculate score
            const long long cut = calculate_cut_size(clique, n, weights);

            if (const long long new_val = static_cast<long long>(clique.size()) * m + cut; new_val > clique_val_rep)
            {
                clique_val_rep = new_val;
                max_clique_rep = clique;
            }
        }
    }

    lower_bound = max_clique_rep[1];
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
    sat_solver->add_clause(-(*y)[{graph->get_highest_degree_vertex(), span / 2 + 1}]);
}

BCPSolver::BCPSolver::BCPSolver(const Graph *graph, const int lower_bound, const int upper_bound)
    : graph(graph), upper_bound(upper_bound), lower_bound(lower_bound)
{
    if (this->upper_bound < 0)
    {
        calculate_upper_bound();
    }

    span = this->upper_bound;

    if (this->lower_bound < 0)
    {
        calculate_lower_bound();
    }
}
BCPSolver::BCPSolver::~BCPSolver()
{
    delete sat_solver;
    delete x;
    delete y;
}

BCPSolver::SOLVER_STATUS BCPSolver::BCPSolver::solve(const double time_limit, const bool find_optimal,
                                                     const bool incremental)
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

        while (result == CaDiCaL::Status::SATISFIABLE && span > lower_bound)
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
    stats["lower_bound"] = lower_bound;
    stats["variables"] = sat_solver_stats["variables"];
    stats["clauses"] = sat_solver_stats["clauses"];
    stats["status"] = status;
    stats["span"] = get_span();
    stats["encoding_time"] = encoding_time;
    stats["total_solving_time"] = sat_solver_stats["total_solving_time"];
    stats["time_used"] = encoding_time + sat_solver_stats["total_solving_time"];

    return stats;
}
