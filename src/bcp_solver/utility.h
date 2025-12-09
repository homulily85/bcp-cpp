//
// Created by homulily85 on 11/29/25.
//

#ifndef BCP_BMCP_UTILITY_H
#define BCP_BMCP_UTILITY_H

#include <string>
#include <vector>

namespace BCPSolver
{
class Graph
{
  private:
    std::vector<std::tuple<int, int, int>> *edges_list;
    std::vector<std::vector<int>> *matrix;
    int n;

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

    void add_edge(const int i, const int j, const int w) const
    {
        edges_list->emplace_back(i, j, w);
        (*matrix)[i][j] = w;
        (*matrix)[j][i] = w;
    }

    [[nodiscard]] const std::vector<std::tuple<int, int, int>> *get_edges() const
    {
        return edges_list;
    }

    [[nodiscard]] int get_weight(int i, int j) const
    {
        return (*matrix)[i][j];
    }

    [[nodiscard]] int get_number_of_nodes() const
    {
        return n;
    }

    [[nodiscard]] int get_number_of_edges() const
    {
        return static_cast<int>(edges_list->size());
    }

    [[nodiscard]] int get_highest_degree_vertex() const;
};

Graph *read_bcp_graph(const std::string &file_path);

} // namespace BCPSolver

#endif // BCP_BMCP_UTILITY_H