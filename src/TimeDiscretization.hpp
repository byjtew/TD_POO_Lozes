#include "unistd.h"

#pragma once

namespace time_discretization {
class ITimeDiscretization {
   protected:
    double start, end;
    size_t nb_steps;

   public:
    double get_start();
    double get_end();
    double get_step();
    size_t get_nb_points();

    size_t iteration(double t_n);
};

class UniformTimeDiscretization : public ITimeDiscretization {
   public:
    UniformTimeDiscretization(double _start, double _end, size_t _n_steps);
};
}  // namespace time_discretization