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

variable::Variable Problem::solve() {
    variable::Variable variables(time);
    double _step = time->get_step();
    std::cout << "--- Solve problem ---" << std::endl;
    std::cout << "--- compute equation initial condition ---" << std::endl;
    getEquation().compute_initial_condition(time->get_start(), variables);
    for (double t = time->get_start() + _step; t <= time->get_end();
         t += _step) {
        std::cout << "--- compute equation at time: ---" << t << std::endl;
        getEquation().compute(t, variables);
    }
    std::cout << "--- Problem solved: " << variables.size() << " results ---" << std::endl;
    return variables;
}

equation::Equation Problem::getEquation() { return equation; }

}  // namespace problem
