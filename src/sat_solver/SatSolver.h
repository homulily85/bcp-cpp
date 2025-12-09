//
// Created by homulily85 on 11/29/25.
//

#ifndef BCP_BMCP_SATSOLVER_H
#define BCP_BMCP_SATSOLVER_H
#include "cadical.hpp"

#include <atomic>
#include <chrono>
#include <limits>
#include <string>
#include <unordered_map>

static constexpr double NO_TIME_LIMIT = std::numeric_limits<double>::lowest();

namespace SATSolver
{
class SatSolver
{
  private:
    int number_of_clauses = 0;
    int number_of_variables = 0;
    CaDiCaL::Solver *solver = new CaDiCaL::Solver();
    std::vector<int> *last_feasible_model = nullptr;
    int status = 0;
    double time_accum = 0.0;

    class AtomicTerminator final : public CaDiCaL::Terminator {
    public:
        std::atomic<bool> force_terminate{false};
        bool terminate() override {
            return force_terminate.load(std::memory_order_relaxed);
        }
    };

  public:
    SatSolver() = default;

    ~SatSolver();

    [[nodiscard]] int create_new_variable();

    void add_clause(const std::vector<int> &clause);

    void add_clause(int l);

    void add_clause(int l1, int l2);

    void add_clause(int l1, int l2, int l3);

    void add_clause(int l1, int l2, int l3, int l4);

    int solve(const std::vector<int> *assumptions = nullptr, double time_limit = NO_TIME_LIMIT);

    [[nodiscard]] std::unordered_map<std::string, double> get_statistics() const;

    void reset();
};

} // namespace SATSolver

#endif // BCP_BMCP_SATSOLVER_H
