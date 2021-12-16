#pragma once

#include "unistd.h"
#include <vector>

namespace time_discretization {
class ITimeDiscretization {
   protected:
    std::vector<double> time_series{};

   public:
    double get_start();
    double get_end();
    double get_step();
    size_t get_nb_points();

    std::vector<double>::iterator begin() { return time_series.begin(); }
    std::vector<double>::iterator end() { return time_series.end(); }

    std::vector<double>::const_iterator cbegin() const {
        return time_series.cbegin();
    }
    std::vector<double>::const_iterator cend() const {
        return time_series.cend();
    }

    size_t iteration(double t_n);
};

class UniformTimeDiscretization : public ITimeDiscretization {
   public:
    UniformTimeDiscretization(double _start, double _end, size_t _n_steps);
};
}  // namespace time_discretization