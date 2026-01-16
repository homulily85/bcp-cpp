#include "bcp_solver/bcp_solver.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        const BCPSolver::ProgramConfig config = BCPSolver::ArgParser::parse(argc, argv);

        const auto* g = BCPSolver::read_bcp_graph(config.filename);
        if (g == nullptr)
        {
            exit(1);
        }
        auto* s = BCPSolver::BCPSolver::create_solver(config.solving_method, g, config.solver, config.upper_bound,
                                                      config.use_symmetry_breaking, config.use_heuristics);;
        s->solve(config.time_limit, config.find_optimal, config.incremental_mode, config.variable_for_incremental);
        for (auto stats = s->get_statistics(); const auto& [fst, snd] : stats)
        {
            std::cout << fst << ": " << snd << '\n';
        }

        delete s;
        delete g;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n\n";
        BCPSolver::ArgParser::printUsage(argv[0]);
        return 1;
    }

    return 0;
}
