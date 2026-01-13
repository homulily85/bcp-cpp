#include "test_common.h"

using BCPSolver::SolverStatus;
using BCPSolver::test::solve_expect;

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, GEOM20_NonOptimal_DummyUpperBound)
{
    for (const bool symm : {false, true})
    {
        for (const bool heur : {false, true})
        {
            constexpr int ub = 100;
            SCOPED_TRACE(std::string(symm ? "symmetry=on" : "symmetry=off") + " / " +
                         (heur ? "heuristic=on" : "heuristic=off"));
            solve_expect(BCPSolver::StaircaseWithoutAuxiliaryVars, "../dataset/GEOM20.col", ub, symm, heur,
                         false, false, SolverStatus::SATISFIABLE, ub);
        }
    }
}

TEST(StaircaseWithoutAuxiliaryVarsEncodingTest, Optimal_NonIncremental_GEOM20_GEOM20a_GEOM20b)
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

    for (const auto& [path, expected_span] : cases)
    {
        for (const bool symm : {false, true})
        {
            for (const bool heur : {false, true})
            {
                SCOPED_TRACE(std::string(path) + " / symmetry=" + (symm ? "on" : "off") + " / heuristic=" +
                    (heur ? "on" : "off"));
                solve_expect(BCPSolver::StaircaseWithoutAuxiliaryVars, path, -1, symm, heur, true, false,
                             SolverStatus::OPTIMAL, expected_span);
            }
        }
    }
}
