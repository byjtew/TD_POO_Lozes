
#pragma once
#include <memory>
#include <vector>

#include "TimeDiscretization.hpp"
#include "unistd.h"

// Defined by CMake [ DEFAULT: 1 ]
// Usage for release: cmake <target> -DCMAKE_BUILD_TYPE=Release
#if !defined(DEBUG_MODE)
#define DEBUG_MODE 1
#endif  // DEBUG_MODE

namespace variable {

class Variable {
   private:
    std::vector<double> values;

    // TODO: Replace with a weak_ptr
    time_discretization::ITimeDiscretization* time_ptr;

   public:
    Variable(time_discretization::ITimeDiscretization* _time_ptr);

    std::vector<double>::iterator begin() { return values.begin(); }
    std::vector<double>::iterator end() { return values.end(); }

    std::vector<double>::const_iterator cbegin() const {
        return values.cbegin();
    }
    std::vector<double>::const_iterator cend() const { return values.cend(); }

    size_t size() const { return values.size(); }

    double operator()(double t_n) const { return values[time_ptr->iteration(t_n)]; }
    double& operator()(double t_n) { return values[time_ptr->iteration(t_n)]; }

    double operator()(size_t idx) const { return values[idx]; }
    double& operator()(size_t idx) { return values[idx]; }

    void print(std::string filename = "results.dat");
    
    time_discretization::ITimeDiscretization getTime() { return *time_ptr; }
};

}  // namespace variable
