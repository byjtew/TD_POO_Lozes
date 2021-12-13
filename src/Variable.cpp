#include "Variable.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include "TimeDiscretization.hpp"

namespace variable {

Variable::Variable(time_discretization::ITimeDiscretization* _time_ptr) {
    time_ptr = _time_ptr;
    values.resize(_time_ptr->get_nb_points()+1);
}

void Variable::print(std::string filename) const {
    std::ofstream of(filename);
    size_t idx = 0;
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    for (const auto& e : values) {
        if (DEBUG_MODE) std::cout << idx << " " << e << std::endl;
        of << idx << " " << e << std::endl;
        idx += 1;
    }
    of.close();
}

}  // namespace variable
