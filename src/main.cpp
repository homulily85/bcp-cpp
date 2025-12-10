#include "bcp_solver/bcp_solver.h"

#include <iostream>
#include <string>

// Structure to hold the parsed arguments


int main(int argc, char *argv[])
{
    try
    {
        const BCPSolver::ProgramConfig config = BCPSolver::ArgParser::parse(argc, argv);

        auto *g = BCPSolver::read_bcp_graph(config.filename);
        if (g == nullptr)
        {
            exit(1);
        }
        auto *s = new BCPSolver::BCPSolver(g, config.upper_bound);
        s->solve(config.time_limit, config.find_optimal, config.incremental_mode);
        for (auto stats = s->get_statistics(); const auto &[fst, snd] : stats)
        {
            std::cout << fst << ": " << snd << '\n';
        }

        delete s;
        delete g;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n\n";
        BCPSolver::ArgParser::printUsage(argv[0]);
        return 1;
    }

    return 0;
}