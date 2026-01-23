//
// Created by homulily85 on 1/13/26.
//

#ifndef BCP_CADICAL_H
#define BCP_CADICAL_H
#include <atomic>

#include "cadical.hpp"
#include "SatSolver.h"

namespace CaDiCaL
{
    class Solver;
}

namespace SATSolver
{
    class Cadical : public SatSolver
    {
    private:
        std::unique_ptr<CaDiCaL::Solver> solver{std::make_unique<CaDiCaL::Solver>()};

        class AtomicTerminator final : public CaDiCaL::Terminator
        {
        public:
            std::atomic<bool> force_terminate{false};

            bool terminate() override
            {
                return force_terminate.load(std::memory_order_relaxed);
            }
        };

        std::unordered_map<std::string, double> stats_accum;

        void capture_and_accumulate_stats();

    public:
        Cadical() = default;

        ~Cadical() override = default;

        void add_clause(const std::vector<int>& clause) override;

        void add_clause(int l) override;

        void add_clause(int l1, int l2) override;

        void add_clause(int l1, int l2, int l3) override;

        void add_clause(int l1, int l2, int l3, int l4) override;

        int solve(const std::vector<int>* assumptions, double time_limit) override;

        void reset() override;

        std::unordered_map<std::string, double> get_statistics() const override;
    };
} // SATSolver

#endif //BCP_CADICAL_H
