//
// Created by homulily85 on 1/13/26.
//

#include "Cadical.h"

#include <condition_variable>

void SATSolver::Cadical::add_clause(const std::vector<int>& clause)
{
    number_of_clauses++;
    solver->clause(clause);
}

void SATSolver::Cadical::add_clause(const int l)
{
    number_of_clauses++;
    solver->clause(l);
    // std::cout << '[' << l << ']' << '\n';
}

void SATSolver::Cadical::add_clause(const int l1, const int l2)
{
    number_of_clauses++;
    if (l1 < l2)
    {
        solver->clause(l1, l2);
    }

    else
    {
        solver->clause(l2, l1);
    }
    // std::cout << '[' << l1 << ", " << l2 << ']' << '\n';
}

void SATSolver::Cadical::add_clause(const int l1, const int l2, const int l3)
{
    number_of_clauses++;
    const int x = std::min({l1, l2, l3});
    const int z = std::max({l1, l2, l3});
    const int y = l1 + l2 + l3 - x - z;
    solver->clause(x, y, z);
    // std::cout << '[' << l1 << ", " << l2 << ", " << l3 << ']' << '\n';
}

void SATSolver::Cadical::add_clause(const int l1, const int l2, const int l3, const int l4)
{
    number_of_clauses++;
    solver->clause(l1, l2, l3, l4);
    // std::cout << '[' << l1 << ", " << l2 << ", " << l3 << ", " << l4 << ']' << '\n';
}

int SATSolver::Cadical::solve(const std::vector<int>* assumptions, const double time_limit)
{
    if (time_limit != NO_TIME_LIMIT && time_limit < 0.0)
    {
        // Time limit already exceeded before we started
        status = CaDiCaL::Status::UNKNOWN;
        return status;
    }

    if (assumptions != nullptr)
    {
        for (const auto assumption : *assumptions)
        {
            solver->assume(assumption);
        }
    }

    const auto start_time = std::chrono::high_resolution_clock::now();

    if (time_limit == NO_TIME_LIMIT)
    {
        status = solver->solve();
    }
    else
    {
        // 1. Create the terminator on the stack (it must outlive the thread usage)
        AtomicTerminator terminator;
        solver->connect_terminator(&terminator);

        // 2. Synchronization primitives
        std::mutex mtx;
        std::condition_variable cv;
        bool finished = false; // Flag to tell timer thread we are done

        // 3. Start the timer thread
        std::thread timer_thread([&]()
        {
            std::unique_lock<std::mutex> lk(mtx);
            // Wait for 'time_limit' OR until 'finished' becomes true.
            // wait_for returns false if it timed out.
            if (!cv.wait_for(lk, std::chrono::duration<double>(time_limit), [&] { return finished; }))
            {
                // If we are here, it means we timed out. Signal termination.
                terminator.force_terminate.store(true, std::memory_order_relaxed);
            }
        });

        // 4. Run the solver (Main Thread)
        status = solver->solve();

        // 5. Signal the timer thread that we finished
        {
            std::lock_guard lk(mtx);
            finished = true;
        }
        cv.notify_one(); // Wake up the timer thread if it's sleeping

        // 6. Safely join the thread.
        // Because of the notification, the thread will wake up and exit immediately
        // if the solver finished early.
        if (timer_thread.joinable())
        {
            timer_thread.join();
        }

        solver->disconnect_terminator();
    }

    time_accum += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();

    return status;
}

void SATSolver::Cadical::reset()
{
    number_of_clauses = 0;
    number_of_variables = 0;
    solver = std::make_unique<CaDiCaL::Solver>();
}