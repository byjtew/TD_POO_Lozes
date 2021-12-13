#include <functional>

#include "Variable.hpp"

#pragma once

namespace equation {

namespace integrations {

class EulerIntegration {
   public:
    static void update(variable::Variable &_variables, double _current_t,
                       double _dt, std::function<double(double)> _f) {
        double prev_t = _current_t - _dt;
        _variables(_current_t) = _f(_current_t - prev_t) + _dt * prev_t;
    }
};

}  // namespace integrations

class Equation {
   private:
    std::function<double(double)> f;

   public:
    Equation(std::function<double(double)> func) : f(func){};
    void compute_initial_condition(double _t_initial,
                                   variable::Variable &_variables) {
        _variables(_t_initial) = f(_t_initial);
    }

    template <class Integrator = integrations::EulerIntegration>
    void compute(double current_t, variable::Variable &_variables) {
        double dt = _variables.getTime().get_step();
        Integrator::update(_variables, current_t, dt, f);
    }

    std::function<double(double)> getFunction() const { return f; }
};

}  // namespace equation
