#include "TimeDiscretization.hpp"

#include <math.h>
#include <unistd.h>

#include <iostream>

namespace time_discretization {

UniformTimeDiscretization::UniformTimeDiscretization(double _start, double _end,
                                                     size_t _nb_steps) {
    if (_start > _end)
        throw std::invalid_argument("start > end");
    else if (_start < 0.0)
        throw std::invalid_argument("start < 0.0");
    else if (_end < 0.0)
        throw std::invalid_argument("end < 0.0");
    else if (_nb_steps <= 0)
        throw std::invalid_argument("nb_steps <= 0");

    start = _start;
    end = _end;
    nb_steps = _nb_steps;
};

double ITimeDiscretization::get_start() { return start; }
double ITimeDiscretization::get_end() { return end; }
double ITimeDiscretization::get_step() {
    return (get_end() - get_start()) / get_nb_points();
}
size_t ITimeDiscretization::get_nb_points() { return nb_steps; }

size_t ITimeDiscretization::iteration(double t_n) {
    return (size_t)std::round(get_nb_points() * t_n /
                              (get_end() - get_start()));
}
}  // namespace time_discretization
