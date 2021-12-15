#pragma once
#include <iostream>
#include <thread>

#include "Equation.hpp"
#include "TimeDiscretization.hpp"
#include "Timer.hpp"
#include "Variable.hpp"

namespace problem {

class Problem {
   private:
    equation::Equation equation;
    time_discretization::ITimeDiscretization* time;

   public:
    Problem(equation::Equation _eq,
            time_discretization::ITimeDiscretization* _time_ptr);

    template <class Integrator = equation::integrations::EulerIntegration>
    variable::Variable solve() {
        if (DEBUG_MODE) std::cout << "--- Solve problem ---" << std::endl;
        variable::Variable variables(time);
        double _step = time->get_step();
        if (DEBUG_MODE)
            std::cout << "--- compute equation initial condition ---"
                      << std::endl;
        getEquation().compute_initial_condition(time->get_start(), variables);
        for (double t = time->get_start() + _step; t <= time->get_end();
             t += _step) {
            if (DEBUG_MODE)
                std::cout << "--- compute equation at time: " << t << " ---"
                          << std::endl;
            getEquation().compute<Integrator>(t, variables);
        }
        return variables;
    }

    template <class Integrator_A, class Integrator_B>
    static std::pair<variable::Variable, variable::Variable> solve_concurrent(
        equation::Equation equation_A, equation::Equation equation_B,
        time_discretization::ITimeDiscretization* time) {
        if (DEBUG_MODE)
            std::cout << "--- Solve problem in concurrent mode ---"
                      << std::endl;
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
            equation_A.compute<Integrator_A>(t, results_A);
            equation_B.compute<Integrator_B>(t, results_B);
        }
        return std::pair<variable::Variable, variable::Variable>(results_A,
                                                                 results_B);
    }

    template <class Integrator_A, class Integrator_B>
    static std::pair<variable::Variable, variable::Variable> solve_parallel(
        problem::Problem& problem_A, problem::Problem& problem_B,
        std::pair<timer::Timer, timer::Timer>& timers) {
        variable::Variable results_A{}, results_B{};
        if (DEBUG_MODE)
            std::cout << "--- Solve problem in parallel mode ---" << std::endl;

        std::thread thread_A([&timers, &results_A, &problem_A]() {
            timers.first.start();
            results_A = problem_A.solve<Integrator_A>();
            timers.first.stop();
        });

        std::thread thread_B([&timers, &results_B, &problem_B]() {
            timers.second.start();
            results_B = problem_B.solve<Integrator_B>();
            timers.second.stop();
        });

        thread_A.join();
        thread_B.join();

        return std::pair<variable::Variable, variable::Variable>(results_A,
                                                                 results_B);
    }

    equation::Equation getEquation() const { return equation; }
};
}  // namespace problem
