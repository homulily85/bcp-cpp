//
// Created by homulily85 on 11/29/25.
//

#ifndef BCP_BMCP_BCP_SOLVER_H
#define BCP_BMCP_BCP_SOLVER_H
#include "../sat_solver/SatSolver.h"
#include "utility.h"

#include <map>
#include <utility>

namespace BCPSolver
{
static constexpr double NO_TIME_LIMIT = std::numeric_limits<double>::lowest();

enum SOLVER_STATUS
{
    UNKNOWN = -1,
    UNSATISFIABLE = 0,
    SATISFIABLE = 1,
    OPTIMAL = 2,
};

class BCPSolver
{
  private:
    const Graph *graph;
    int upper_bound;

    SATSolver::SatSolver *sat_solver = new SATSolver::SatSolver();
    SOLVER_STATUS status = UNKNOWN;

    int span;

    double encoding_time = 0.0;

    // Vertex u has color i
    std::map<std::pair<int, int>, int> *x = nullptr;
    // Vertex u has color greater or equal to i
    std::map<std::pair<int, int>, int> *y = nullptr;

    void calculate_upper_bound();

    void create_variable();

    void encode();

    void first_constraint() const;

    void second_constraint() const;

    void third_constraint() const;

    void fourth_constraint() const;

    void symmetry_breaking() const;

  public:
    explicit BCPSolver(const Graph *graph, int upper_bound = -1);

    ~BCPSolver();

    SOLVER_STATUS solve(double time_limit = NO_TIME_LIMIT, bool find_optimal = false, bool incremental = false);

    [[nodiscard]] int get_span() const
    {
        return (status != UNKNOWN && status != UNSATISFIABLE) ? span : -1;
    }

    [[nodiscard]] std::unordered_map<std::string, double> get_statistics() const;
};

} // namespace BCPSolver

#endif // BCP_BMCP_BCP_SOLVER_H
