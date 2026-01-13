#pragma once

#include "bcp_solver/bcp_solver.h"
#include "bcp_solver/utility.h"
#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace BCPSolver::test
{
    struct GraphDeleter
    {
        void operator()(const Graph* g) const noexcept { delete g; }
    };

    inline std::unique_ptr<Graph, GraphDeleter> load_graph(const std::string& rel_path)
    {
        auto* g = read_bcp_graph(rel_path);
        EXPECT_NE(g, nullptr) << "Failed to load graph: " << rel_path;
        return std::unique_ptr<Graph, GraphDeleter>(g);
    }

    inline std::unique_ptr<BCPSolver> make_solver(const SolvingMethod method,
                                                  const Graph* g,
                                                  const int upper_bound,
                                                  const bool use_symmetry_breaking,
                                                  const bool use_heuristic)
    {
        return std::unique_ptr<BCPSolver>(
            BCPSolver::create_solver(method, g, upper_bound, use_symmetry_breaking, use_heuristic));
    }

    inline void solve_expect(const SolvingMethod method,
                             const std::string& rel_graph_path,
                             const int upper_bound,
                             const bool use_symmetry_breaking,
                             const bool use_heuristic,
                             const bool find_optimal,
                             const bool incremental,
                             const std::string& variable_for_incremental,
                             const SolverStatus expected_status,
                             const int expected_span)
    {
        const auto g = load_graph(rel_graph_path);
        if (!g) return;

        const auto s = make_solver(method, g.get(), upper_bound, use_symmetry_breaking, use_heuristic);
        ASSERT_NE(s, nullptr);

        const auto status = s->solve(NO_TIME_LIMIT, find_optimal, incremental, variable_for_incremental);
        EXPECT_EQ(status, expected_status);
        EXPECT_EQ(s->get_span(), expected_span);
    }
} // namespace BCPSolver::test
