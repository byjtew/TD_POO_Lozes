#pragma once
#include <iostream>

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

    static std::pair<variable::Variable, variable::Variable> solve_concurrent(
        equation::Equation equation_A, equation::Equation equation_B,
        time_discretization::ITimeDiscretization* time);

    static std::pair<variable::Variable, variable::Variable> solve_parallel(
        problem::Problem& problem_A, problem::Problem& problem_B,
        std::pair<timer::Timer, timer::Timer>& timers);

    equation::Equation getEquation() const { return equation; }
};
}  // namespace problem
