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
    timer::Timer solve_timer;

   public:
    Problem(equation::Equation _eq,
            time_discretization::ITimeDiscretization* _time_ptr);

    variable::Variable solve(std::string result_filename = "results.dat");

    static std::pair<variable::Variable, variable::Variable> solve_concurrent(
        equation::Equation equation_A, equation::Equation equation_B,
        time_discretization::ITimeDiscretization* time, timer::Timer& timer,
        std::string result_filename_A = "results_A.dat",
        std::string result_filename_B = "results_B.dat");

    static std::pair<variable::Variable, variable::Variable> solve_parallel(
        problem::Problem& problem_A, problem::Problem& problem_B,
        std::string result_filename_A = "results_A.dat",
        std::string result_filename_B = "results_B.dat");

    equation::Equation getEquation() const { return equation; }
};
}  // namespace problem
