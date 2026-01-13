#ifndef BCP_MAXSATSOLVER_H
#define BCP_MAXSATSOLVER_H

#include <chrono>
#include <limits>
#include <string>
#include <unordered_map>

static constexpr double NO_TIME_LIMIT = std::numeric_limits<double>::lowest();

namespace SATSolver
{
    class MaxSatSolver
    {
    private:
        int number_of_variables{};
        std::vector<std::vector<int>> clauses{};
        int status{};
        double time_accum{};

    public:
        MaxSatSolver() = default;

        ~MaxSatSolver() = default;

        [[nodiscard]] int create_new_variable();

        void add_clause(const std::vector<int>& clause);

        void add_clause(int l);

        void add_clause(int l1, int l2);

        void add_clause(int l1, int l2, int l3);

        void add_clause(int l1, int l2, int l3, int l4);

        int solve(const std::vector<int>* assumptions = nullptr, double time_limit = NO_TIME_LIMIT);

        [[nodiscard]] std::unordered_map<std::string, double> get_statistics() const;

        void reset();

        void encode_equals_k(const std::vector<int>& vars, int k);
    };
} // namespace SATSolver

#endif // BCP_MAXSATSOLVER_H
