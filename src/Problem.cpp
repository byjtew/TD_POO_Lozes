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
    solve_timer = timer::Timer{};
}

variable::Variable Problem::solve(std::string result_filename) {
    if (DEBUG_MODE) std::cout << "--- Solve problem ---" << std::endl;
    variable::Variable variables(time);
    double _step = time->get_step();
    if (DEBUG_MODE)
        std::cout << "--- compute equation initial condition ---" << std::endl;
    solve_timer.start();
    getEquation().compute_initial_condition(time->get_start(), variables);
    for (double t = time->get_start() + _step; t <= time->get_end();
         t += _step) {
        if (DEBUG_MODE)
            std::cout << "--- compute equation at time: ---" << t << std::endl;
        getEquation().compute(t, variables);
    }
    solve_timer.stop();
    variables.print(result_filename);
    return variables;
}

std::pair<variable::Variable, variable::Variable> Problem::solve_concurrent(
    equation::Equation equation_A, equation::Equation equation_B,
    time_discretization::ITimeDiscretization* time, timer::Timer& timer,
    std::string result_filename_A, std::string result_filename_B) {
    if (DEBUG_MODE)
        std::cout << "--- Solve problem in concurrent mode ---" << std::endl;
    variable::Variable results_A(time), results_B(time);

    double _step = time->get_step();
    if (DEBUG_MODE)
        std::cout << "--- compute equations initial conditions ---"
                  << std::endl;

    timer.start();
    equation_A.compute_initial_condition(time->get_start(), results_A);
    equation_B.compute_initial_condition(time->get_start(), results_B);
    for (double t = time->get_start() + _step; t <= time->get_end();
         t += _step) {
        if (DEBUG_MODE)
            std::cout << "--- compute equation at time: ---" << t << std::endl;
        equation_A.compute(t, results_A);
        equation_B.compute(t, results_B);
    }

    timer.stop();
    results_A.print(result_filename_A);
    results_B.print(result_filename_B);
    return std::pair<variable::Variable, variable::Variable>(results_A,
                                                             results_B);
}

std::pair<variable::Variable, variable::Variable> Problem::solve_parallel(
    problem::Problem& problem_A, problem::Problem& problem_B,
    std::string result_filename_A, std::string result_filename_B) {
    variable::Variable results_A{}, results_B{};

    std::thread thread_A(
        [&results_A, &problem_A]() { results_A = problem_A.solve(); });

    std::thread thread_B(
        [&results_B, &problem_B]() { results_B = problem_B.solve(); });

    thread_A.join();
    thread_B.join();

    return std::pair<variable::Variable, variable::Variable>(results_A,
                                                             results_B);
}

}  // namespace problem
