#include <functional>

#include "Variable.hpp"

#pragma once

namespace equation {

class Equation {
   private:
    std::function<double(double)> f;

   public:
    Equation(std::function<double(double)> func) : f(func){};
    void compute_initial_condition(double _t_initial,
                                   variable::Variable &_variables);
    void compute(double current_t, variable::Variable &_variables);

    std::function<double(double)> getFunction() { return f; }
};

}  // namespace equation
