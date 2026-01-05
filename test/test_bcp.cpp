//
// Created by homulily85 on 12/10/25.
//

#include "bcp_solver/bcp_solver.h"
#include <gtest/gtest.h>

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, dummyUpperBound, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, dummyUpperBound, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, dummyUpperBound, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, dummyUpperBound, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, dummyUpperBound, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, dummyUpperBound, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, dummyUpperBound, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, dummyUpperBound, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, dummyUpperBound, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, dummyUpperBound, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, dummyUpperBound, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, dummyUpperBound, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, dummyUpperBound, false,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, dummyUpperBound, true,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsNoCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsNoCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, dummyUpperBound, false,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, dummyUpperBound, true,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20NonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20aNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, TestGEOM20bNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, dummyUpperBound, false,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, dummyUpperBound, true,
                                                  false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20NonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20aNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20aNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20aNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20aNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20bNonIncrementalOptimalWithoutAnything)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20bNonIncrementalOptimalWithSymetryBreaking)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, false);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20bNonIncrementalOptimalWithHeuristic)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, false, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, TestGEOM20bNonIncrementalOptimalWithBoth)
{
    auto* g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto* s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithoutAuxiliaryVars, g, -1, true, true);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}