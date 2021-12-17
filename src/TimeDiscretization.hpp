#pragma once

#include <vector>

#include "unistd.h"

namespace time_discretization {
class ITimeDiscretization {
   protected:
    std::vector<double> time_series{};

   public:
    virtual double get_start();
    virtual double get_end();
    virtual double get_step();
    virtual size_t get_nb_points();

    std::vector<double>::iterator begin() { return time_series.begin(); }
    std::vector<double>::iterator end() { return time_series.end(); }

    std::vector<double>::const_iterator cbegin() const {
        return time_series.cbegin();
    }
    std::vector<double>::const_iterator cend() const {
        return time_series.cend();
    }

    virtual size_t iteration(double t_n);
};

class UniformTimeDiscretization : public ITimeDiscretization {
   public:
    UniformTimeDiscretization(double _start, double _end, size_t _n_steps);
};
}  // namespace time_discretization