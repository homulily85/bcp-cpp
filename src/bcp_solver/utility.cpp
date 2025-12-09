//
// Created by homulily85 on 11/29/25.
//

#include "utility.h"

#include <fstream>
#include <iostream>
#include <sstream>

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
