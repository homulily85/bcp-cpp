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
    protected:
        const Graph* graph{};
        int upper_bound{};
        int lower_bound{};

        SATSolver::SatSolver sat_solver{SATSolver::SatSolver()};
        SolverStatus status{UNKNOWN};

        double encoding_time{};

        void calculate_upper_bound();

        // Vertex u has color i
        std::map<std::pair<int, int>, int> x{};
        // Vertex u has color greater or equal to i || Vertex u has color less or equal to i
        std::map<std::pair<int, int>, int> y{};

        int span{};

        virtual void create_variable() =0;

        virtual void encode() =0;

        virtual std::vector<int>* create_assumptions() =0;

        explicit BCPSolver(const Graph* graph, int upper_bound = -1);

    public:
        BCPSolver(const BCPSolver& other) = delete;
        void operator=(const BCPSolver&) = delete;

        virtual ~BCPSolver() = default;

        static BCPSolver* create_solver(SolvingMethod method, const Graph* graph, int upper_bound = -1);

        SolverStatus non_optimal_solving(double time_limit);

        SolverStatus optimal_solving_non_incremental(double time_limit);
        SolverStatus optimal_solving_incremental(double time_limit);

        SolverStatus solve(double time_limit = NO_TIME_LIMIT, bool find_optimal = false, bool incremental = false);

        [[nodiscard]] int get_span() const;

        [[nodiscard]] std::unordered_map<std::string, double> get_statistics() const;
    };
} // namespace BCPSolver

#endif // BCP_BMCP_BCP_SOLVER_H
