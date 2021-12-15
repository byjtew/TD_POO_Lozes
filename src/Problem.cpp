#include "Problem.hpp"

#include <iostream>
#include <thread>

#include "Equation.hpp"
#include "TimeDiscretization.hpp"
#include "Timer.hpp"
#include "Variable.hpp"

namespace problem {

Problem::Problem(equation::Equation _eq,
                 time_discretization::ITimeDiscretization* _time_ptr)
    : equation(_eq) {
    if (_time_ptr == nullptr)
        throw std::invalid_argument("_time_ptr is nullptr");
    time = _time_ptr;
}

std::pair<variable::Variable, variable::Variable> Problem::solve_concurrent(
    equation::Equation equation_A, equation::Equation equation_B,
    time_discretization::ITimeDiscretization* time) {
    if (DEBUG_MODE)
        std::cout << "--- Solve problem in concurrent mode ---" << std::endl;
    variable::Variable results_A(time), results_B(time);

    double _step = time->get_step();
    if (DEBUG_MODE)
        std::cout << "--- compute equations initial conditions ---"
                  << std::endl;

    equation_A.compute_initial_condition(time->get_start(), results_A);
    equation_B.compute_initial_condition(time->get_start(), results_B);
    for (double t = time->get_start() + _step; t <= time->get_end();
         t += _step) {
        if (DEBUG_MODE)
            std::cout << "--- compute equations at time: " << t << " ---"
                      << std::endl;
        equation_A.compute(t, results_A);
        equation_B.compute(t, results_B);
    }
    return std::pair<variable::Variable, variable::Variable>(results_A,
                                                             results_B);
}

std::pair<variable::Variable, variable::Variable> Problem::solve_parallel(
    problem::Problem& problem_A, problem::Problem& problem_B,
    std::pair<timer::Timer, timer::Timer>& timers) {
    variable::Variable results_A{}, results_B{};
    if (DEBUG_MODE)
        std::cout << "--- Solve problem in parallel mode ---" << std::endl;

    std::thread thread_A([&timers, &results_A, &problem_A]() {
        timers.first.start();
        results_A = problem_A.solve();
        timers.first.stop();
    });

    std::thread thread_B([&timers, &results_B, &problem_B]() {
        timers.second.start();
        results_B = problem_B.solve();
        timers.second.stop();
    });

    thread_A.join();
    thread_B.join();

    return std::pair<variable::Variable, variable::Variable>(results_A,
                                                             results_B);
}

}  // namespace problem
