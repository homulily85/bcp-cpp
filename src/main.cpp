#include "bcp_solver/bcp_solver.h"

#include <iostream>
#include <stdexcept>
#include <string>

// Structure to hold the parsed arguments
struct ProgramConfig
{
    std::string filename;
    double time_limit;
    int upper_bound;
    bool find_optimal;
    bool incremental_mode;

    // Constructor with defaults
    ProgramConfig() : time_limit(BCPSolver::NO_TIME_LIMIT), upper_bound(-1), find_optimal(true), incremental_mode(false)
    {
    }
};

class ArgParser
{
  public:
    // Helper to print usage instructions
    static void printUsage(const char *programName)
    {
        std::cerr << "Usage: " << programName << " <filename> [options]\n"
                  << "Options:\n"
                  << "  -t, --time_limit <int>       Set time limit (Default: NO_TIME_LIMIT)\n"
                  << "  -ub, --upper_bound           Set preferred upper bound\n"
                  << "  --no-optimal                 Disable finding optimal value (Default: enabled)\n"
                  << "  -i, --incremental            Enable incremental mode (Default: disabled)\n"
                  << "  -h, --help                   Show this help message\n";
    }

    // Main parsing logic
    static ProgramConfig parse(int argc, char *argv[])
    {
        ProgramConfig config;
        bool filenameFound = false;

        // Iterate starting from 1 to skip program name
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                printUsage(argv[0]);
                exit(0); // Exit gracefully if help is requested
            }
            else if (arg == "-t" || arg == "--time_limit")
            {
                if (i + 1 < argc)
                {
                    try
                    {
                        config.time_limit = std::stoi(argv[++i]); // Increment i to consume value
                        if (config.time_limit < 0)
                        {
                            throw std::invalid_argument("Invalid integer for time limit: " + std::string(argv[i]));
                        }
                    }
                    catch (const std::exception &)
                    {
                        throw std::invalid_argument("Invalid integer for time limit: " + std::string(argv[i]));
                    }
                }
                else
                {
                    throw std::invalid_argument("Missing value for time limit flag");
                }
            }
            else if (arg == "-ub" || arg == "--upper_bound")
            {
                if (i + 1 < argc)
                {
                    try
                    {
                        config.upper_bound = std::stoi(argv[++i]); // Increment i to consume value
                        if (config.upper_bound < 0)
                        {
                            throw std::invalid_argument("Invalid integer for upper_bound: " + std::string(argv[i]));
                        }
                    }
                    catch (const std::exception &)
                    {
                        throw std::invalid_argument("Invalid integer for upper_bound: " + std::string(argv[i]));
                    }
                }
                else
                {
                    throw std::invalid_argument("Missing value for upper bound flag");
                }
            }
            else if (arg == "--no-optimal")
            {
                config.find_optimal = false; // Flag to disable
            }
            else if (arg == "-i" || arg == "--incremental")
            {
                config.incremental_mode = true; // Flag to enable
            }
            else if (arg[0] == '-')
            {
                throw std::invalid_argument("Unknown flag: " + arg);
            }
            else
            {
                // Parse filename (first non-flag argument)
                if (filenameFound)
                {
                    throw std::invalid_argument("Multiple filenames provided or invalid argument order: " + arg);
                }
                config.filename = arg;
                filenameFound = true;
            }
        }

        // 1. Check compulsory argument: Filename
        if (!filenameFound)
        {
            throw std::runtime_error("Missing compulsory argument: filename");
        }

        return config;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        const ProgramConfig config = ArgParser::parse(argc, argv);

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
        ArgParser::printUsage(argv[0]);
        return 1;
    }

    return 0;
}