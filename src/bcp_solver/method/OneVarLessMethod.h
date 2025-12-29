//
// Created by homulily85 on 12/30/25.
//

#ifndef BCP_ONEVARLESSMETHOD_H
#define BCP_ONEVARLESSMETHOD_H
#include "bcp_solver/bcp_solver.h"


namespace BCPSolver
{
    class OneVarLessMethod : public BCPSolver
    {
    private:

        void symmetry_breaking();

        void first_constraint();

        void second_constraint();

        void third_constraint();

        void encode() override;

        void create_variable() override;

        std::vector<int>* create_assumptions() override;

    protected:
        friend class BCPSolver;

        explicit OneVarLessMethod(const Graph* graph, const int upper_bound = -1) : BCPSolver(graph, upper_bound)
        {
        }
    };
}


#endif //BCP_ONEVARLESSMETHOD_H
