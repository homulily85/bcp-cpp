//
// Created by homulily85 on 11/29/25.
//

#ifndef BCP_BMCP_UTILITY_H
#define BCP_BMCP_UTILITY_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace BCPSolver
{
static constexpr double NO_TIME_LIMIT = std::numeric_limits<double>::lowest();

class Graph
{
  private:
    std::vector<std::tuple<int, int, int>> *edges_list{};
    std::vector<std::vector<int>> *matrix{};
    int n{};

  public:
    explicit Graph(const int n)
        : edges_list(new std::vector<std::tuple<int, int, int>>()), matrix(new std::vector(n, std::vector<int>(n))),
          n(n)
    {
    }

    ~Graph()
    {
        delete edges_list;
        delete matrix;
    }

    void add_edge(int i, int j, int w) const;

    [[nodiscard]] const std::vector<std::tuple<int, int, int>> *get_edges() const;

    [[nodiscard]] int get_weight(int i, int j) const;

    [[nodiscard]] int get_number_of_nodes() const;

    [[nodiscard]] int get_number_of_edges() const;

    [[nodiscard]] int get_highest_degree_vertex() const;
};

Graph *read_bcp_graph(const std::string &file_path);

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
    static void printUsage(const char *programName);

    static ProgramConfig parse(int argc, char *argv[]);
};

} // namespace BCPSolver

#endif // BCP_BMCP_UTILITY_H