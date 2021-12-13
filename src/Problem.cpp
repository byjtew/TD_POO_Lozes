#include "Problem.hpp"

#include <iostream>

#include "Equation.hpp"
#include "TimeDiscretization.hpp"
#include "Variable.hpp"

namespace problem {

Problem::Problem(equation::Equation _eq,
                 time_discretization::ITimeDiscretization* _time_ptr)
    : equation(_eq) {
    if (_time_ptr == nullptr)
        throw std::invalid_argument("_time_ptr is nullptr");
    time = _time_ptr;
}

variable::Variable Problem::solve(std::string result_filename) {
    if (DEBUG_MODE) std::cout << "--- Solve problem ---" << std::endl;
    variable::Variable variables(time);
    double _step = time->get_step();
    if (DEBUG_MODE)
        std::cout << "--- compute equation initial condition ---" << std::endl;
    getEquation().compute_initial_condition(time->get_start(), variables);
    for (double t = time->get_start() + _step; t <= time->get_end();
         t += _step) {
        if (DEBUG_MODE)
            std::cout << "--- compute equation at time: ---" << t << std::endl;
        getEquation().compute(t, variables);
    }
    variables.print(result_filename);
    return variables;
}

equation::Equation Problem::getEquation() { return equation; }

}  // namespace problem
