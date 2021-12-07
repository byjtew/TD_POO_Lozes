#include "Equation.hpp"
#include "Variable.hpp"
#include "TimeDiscretization.hpp"
#pragma once

namespace problem {

class Problem {
   private:
    equation::Equation equation;
    time_discretization::ITimeDiscretization* time;

   public:
    Problem(equation::Equation _eq,
            time_discretization::ITimeDiscretization* _time_ptr);
    variable::Variable solve();

    equation::Equation getEquation();
};
}  // namespace problem
