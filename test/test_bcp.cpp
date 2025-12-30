//
// Created by homulily85 on 12/10/25.
//

#include "bcp_solver/bcp_solver.h"
#include <gtest/gtest.h>

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g, dummyUpperBound);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g, dummyUpperBound);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20NonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20UsingIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20aIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableGreaterEncodingTest, TestGEOM20bIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesGreater, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g, dummyUpperBound);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20NonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20aIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(TwoVariableLessEncodingTest, TestGEOM20bIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::TwoVariablesLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g, dummyUpperBound);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20NonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20UsingIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20aIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(OneVariableLessEncodingTest, TestGEOM20bIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::OneVariableLess, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, true);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsEncodingTest, TestGEOM20NonOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    constexpr auto dummyUpperBound = 100;
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVars, g, dummyUpperBound);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, false, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::SATISFIABLE);
    EXPECT_EQ(span, dummyUpperBound);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsEncodingTest, TestGEOM20NonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVars, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 21);

    delete s;
    delete g;
}


TEST(StaircaseWithAuxiliaryVarsEncodingTest, TestGEOM20aNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20a.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVars, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 20);

    delete s;
    delete g;
}

TEST(StaircaseWithAuxiliaryVarsEncodingTest, TestGEOM20bNonIncrementalOptimal)
{
    auto *g = BCPSolver::read_bcp_graph("../dataset/GEOM20b.col");
    if (g == nullptr)
    {
        exit(1);
    }
    auto *s = BCPSolver::BCPSolver::create_solver(BCPSolver::StaircaseWithAuxiliaryVars, g);
    const auto result = s->solve(BCPSolver::NO_TIME_LIMIT, true, false);
    const auto span = s->get_span();
    EXPECT_EQ(result, BCPSolver::SolverStatus::OPTIMAL);
    EXPECT_EQ(span, 13);

    delete s;
    delete g;
}
