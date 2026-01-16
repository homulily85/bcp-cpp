#include "test_common.h"

using BCPSolver::SolverStatus;
using BCPSolver::test::solve_expect;

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, GEOM20_NonOptimal_DummyUpperBound_SymmetryOnOff)
{
    for (const auto& solver : {SATSolver::SOLVER::KISSAT, SATSolver::SOLVER::CADICAL})
    {
        for (const bool symm : {false, true})
        {
            for (const bool heur : {false, true})
            {
                constexpr int ub = 100;
                SCOPED_TRACE(std::string(symm ? "symmetry=on" : "symmetry=off") + " / " +
                    (heur ? "heuristic=on" : "heuristic=off"));
                solve_expect(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, "../dataset/GEOM20.col", solver, ub, symm,
                             heur, false, false, "", SolverStatus::SATISFIABLE, ub);
            }
        }
    }
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, Optimal_NonIncremental_GEOM20_GEOM20a_GEOM20b)
{
    struct Case
    {
        const char* path;
        int expected_span;
    };
    constexpr Case cases[] = {
        {"../dataset/GEOM20.col", 21},
        {"../dataset/GEOM20a.col", 20},
        {"../dataset/GEOM20b.col", 13}
    };
    for (const auto& solver : {SATSolver::SOLVER::KISSAT, SATSolver::SOLVER::CADICAL})
    {
        for (const auto& [path, expected_span] : cases)
        {
            for (const bool symm : {false, true})
            {
                for (const bool heur : {false, true})
                {
                    SCOPED_TRACE(std::string(path) + " / symmetry=" + (symm ? "on" : "off") + " / heuristic=" +
                        (heur ? "on" : "off"));
                    solve_expect(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, path, solver, -1, symm, heur, true,
                                 false, "", SolverStatus::OPTIMAL, expected_span);
                }
            }
        }
    }
}

TEST(StaircaseWithAuxiliaryVarsWithCacheEncodingTest, Optimal_Incremental_GEOM20_GEOM20a_GEOM20b)
{
    struct Case
    {
        const char* path;
        int expected_span;
    };
    constexpr Case cases[] = {
        {"../dataset/GEOM20.col", 21},
        {"../dataset/GEOM20a.col", 20},
        {"../dataset/GEOM20b.col", 13}
    };

    for (const auto& solver : {SATSolver::SOLVER::CADICAL})
    {
        for (const auto& [path, expected_span] : cases)
        {
            for (const bool symm : {false, true})
            {
                for (const bool heur : {false, true})
                {
                    SCOPED_TRACE(std::string(path) + " / symmetry=" + (symm ? "on" : "off") + " / heuristic=" +
                        (heur ? "on" : "off"));
                    solve_expect(BCPSolver::StaircaseWithAuxiliaryVarsWithCache, path, solver, -1, symm, heur, true,
                                 true, "x", SolverStatus::OPTIMAL, expected_span);
                }
            }
        }
    }
}
