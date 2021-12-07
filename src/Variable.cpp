#include "Variable.hpp"
#include "TimeDiscretization.hpp"

namespace variable {

Variable::Variable(time_discretization::ITimeDiscretization *_time_ptr) {
    time_ptr = _time_ptr;
    values.resize(_time_ptr->get_nb_points());
}

}  // namespace variable
