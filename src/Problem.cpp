#include "Problem.hpp"


#include "Equation.hpp"
#include "TimeDiscretization.hpp"
#include "Timer.hpp"
#include "Variable.hpp"

namespace problem {

Problem::Problem(equation::Equation _eq,
                 time_discretization::ITimeDiscretization* _time_ptr)
    : equation(_eq) {
    if (_time_ptr == nullptr)
        throw std::invalid_argument("_time_ptr is nullptr");
    time = _time_ptr;
}

}  // namespace problem
