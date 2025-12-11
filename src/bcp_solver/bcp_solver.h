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

class BCPSolver
{
  private:
    const Graph *graph{};
    int upper_bound{};
    int lower_bound{};

    SATSolver::SatSolver *sat_solver{new SATSolver::SatSolver()};
    SolverStatus status{UNKNOWN};

    int span{};

    double encoding_time{};

    SolvingMethod method{};

    // Vertex u has color i
    std::map<std::pair<int, int>, int> *x{};
    // Vertex u has color greater or equal to i || Vertex u has color less or equal to i
    std::map<std::pair<int, int>, int> *y{};

    void calculate_upper_bound();

    void create_variable();

    void encode();

    void one_variable_greater_first_constraint() const;

    void one_variable_greater_second_constraint() const;

    void one_variable_greater_third_constraint() const;

    void one_variable_less_first_constraint() const;

    void one_variable_less_second_constraint() const;

    void one_variable_less_third_constraint() const;

    void two_variables_greater_first_constraint() const;

    void two_variables_greater_second_constraint() const;

    void two_variables_greater_third_constraint() const;

    void two_variables_greater_fourth_constraint() const;

    void two_variables_less_first_constraint() const;

    void two_variables_less_second_constraint() const;

    void two_variables_less_third_constraint() const;

    void two_variables_less_fourth_constraint() const;

    void symmetry_breaking() const;

  public:
    explicit BCPSolver(SolvingMethod method, const Graph *graph, int upper_bound = -1);

    ~BCPSolver();
    SolverStatus non_optimal_solving(double time_limit);

    SolverStatus optimal_solving_non_incremental(double time_limit);
    SolverStatus optimal_solving_incremental(double time_limit);

    SolverStatus solve(double time_limit = NO_TIME_LIMIT, bool find_optimal = false, bool incremental = false);

    [[nodiscard]] int get_span() const;

    [[nodiscard]] std::unordered_map<std::string, double> get_statistics() const;
};

} // namespace BCPSolver

#endif // BCP_BMCP_BCP_SOLVER_H
