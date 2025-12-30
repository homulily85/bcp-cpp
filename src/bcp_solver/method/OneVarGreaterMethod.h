//
// Created by homulily85 on 12/30/25.
//

#ifndef BCP_ONEVARGREATERMETHOD_H
#define BCP_ONEVARGREATERMETHOD_H
#include "bcp_solver/bcp_solver.h"

namespace BCPSolver
{
    class OneVarGreaterMethod : public BCPSolver
    {
    private:
        void first_constraint();

        void second_constraint();

        void third_constraint();

        void symmetry_breaking();

        void encode() override;

        void create_variable() override;

        std::vector<int>* create_assumptions() override;

        friend class BCPSolver;

        explicit OneVarGreaterMethod(const Graph* graph, const int upper_bound = -1) : BCPSolver(graph, upper_bound)
        {
        }
    };
}


#endif //BCP_ONEVARGREATERMETHOD_H
