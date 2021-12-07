#include "Variable.hpp"

#include <gtest/gtest.h>

#include "TimeDiscretization.hpp"

TEST(VariableTest, EmptyTest) {
    auto time = time_discretization::UniformTimeDiscretization(0.0, 2.0, 2);
    variable::Variable var(&time);
}
