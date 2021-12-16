#include "TimeDiscretization.hpp"

#include <math.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <vector>

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

    double step = (_end - _start) / (_nb_steps-1);
    time_series.resize(_nb_steps);
    for (size_t t = 0; t < time_series.size(); t++)
        time_series[t] = _start + t * step;
};

double ITimeDiscretization::get_start() { return time_series.front(); }
double ITimeDiscretization::get_end() { return time_series.back(); }
double ITimeDiscretization::get_step() {
    return (get_end() - get_start()) / get_nb_points();
}
size_t ITimeDiscretization::get_nb_points() { return time_series.size(); }

size_t ITimeDiscretization::iteration(double t_n) {
    double percent = (t_n - get_start()) / (get_end() - get_start());
    auto begin_it_adjusted =
        (time_series.begin() + percent * (time_series.size() - 1));

    // The most it could possibly iterate is 2 elements
    auto it = std::find(begin_it_adjusted, time_series.end(), t_n);

    return it - time_series.begin();
}
}  // namespace time_discretization
