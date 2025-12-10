//
// Created by homulily85 on 11/29/25.
//

#include "utility.h"

#include <fstream>
#include <iostream>
#include <sstream>

void BCPSolver::Graph::add_edge(const int i, const int j, const int w) const
{
    edges_list->emplace_back(i, j, w);
    (*matrix)[i][j] = w;
    (*matrix)[j][i] = w;
}

const std::vector<std::tuple<int, int, int>> *BCPSolver::Graph::get_edges() const
{
    return edges_list;
}

int BCPSolver::Graph::get_weight(int i, int j) const
{
    return (*matrix)[i][j];
}

int BCPSolver::Graph::get_number_of_nodes() const
{
    return n;
}

int BCPSolver::Graph::get_number_of_edges() const
{
    return static_cast<int>(edges_list->size());
}

int BCPSolver::Graph::get_highest_degree_vertex() const
{
    if (n == 0)
    {
        return -1;
    }

    std::vector degrees(n, 0);

    for (const auto &edge : *edges_list)
    {
        degrees[std::get<0>(edge)]++;
        degrees[std::get<1>(edge)]++;
    }

    int max_degree = -1;
    int max_vertex = -1;

    for (int i = 0; i < n; ++i)
    {
        if (degrees[i] > max_degree)
        {
            max_degree = degrees[i];
            max_vertex = i;
        }
    }

    return max_vertex;
}

BCPSolver::Graph *BCPSolver::read_bcp_graph(const std::string &file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return nullptr;
    }

    Graph *g = nullptr;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        char line_type;
        ss >> line_type;

        if (line_type == 'p')
        {
            std::string ignore;
            int num_nodes;
            ss >> ignore >> num_nodes;

            g = new Graph(num_nodes);
        }
        else if (line_type == 'e')
        {
            if (g == nullptr)
                continue;

            int u, v, w;
            ss >> u >> v >> w;

            if (u != v)
            {
                g->add_edge(u - 1, v - 1, w);
            }
        }
    }

    file.close();
    return g;
}

void BCPSolver::ArgParser::printUsage(const char *programName)
{
    std::cerr << "Usage: " << programName << " <filename> [options]\n"
              << "Options:\n"
              << "  -t, --time_limit <int>       Set time limit (Default: NO_TIME_LIMIT)\n"
              << "  -ub, --upper_bound           Set preferred upper bound\n"
              << "  --no-optimal                 Disable finding optimal value (Default: enabled)\n"
              << "  -i, --incremental            Enable incremental mode (Default: disabled)\n"
              << "  -h, --help                   Show this help message\n";
}

BCPSolver::ProgramConfig BCPSolver::ArgParser::parse(int argc, char *argv[])
{
    ProgramConfig config;
    bool filenameFound = false;

    // Iterate starting from 1 to skip program name
    for (int i = 1; i < argc; ++i)
    {

        if (std::string arg = argv[i]; arg == "-h" || arg == "--help")
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

    if (!filenameFound)
    {
        throw std::runtime_error("Missing compulsory argument: filename");
    }

    return config;
}
