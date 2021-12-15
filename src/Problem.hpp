#pragma once

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

    variable::Variable solve();

    static std::pair<variable::Variable, variable::Variable> solve_concurrent(
        equation::Equation equation_A, equation::Equation equation_B,
        time_discretization::ITimeDiscretization* time);

    static std::pair<variable::Variable, variable::Variable> solve_parallel(
        problem::Problem& problem_A, problem::Problem& problem_B, std::pair<timer::Timer, timer::Timer> &timers);

    equation::Equation getEquation() const { return equation; }
};
}  // namespace problem
