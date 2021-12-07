#include "Equation.hpp"

#include <iostream>

#include "Variable.hpp"

namespace equation {

void Equation::compute_initial_condition(double _t_initial,
                                         variable::Variable &_variables) {
    _variables(_t_initial) = f(_t_initial);
}
void Equation::compute(double _current_t, variable::Variable &_variables) {
    double prev_t = _current_t - _variables.getTime().get_step();
    double dt = std::abs(_current_t - prev_t);
    _variables(_current_t) = f(_current_t-prev_t) + dt * prev_t;
}

}  // namespace equation
