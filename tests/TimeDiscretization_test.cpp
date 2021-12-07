#include "TimeDiscretization.hpp"

#include <gtest/gtest.h>

#include "Equation.hpp"
#include "Problem.hpp"

TEST(TimeDiscretizationTest, AllIterationIndexesFound) {
    time_discretization::UniformTimeDiscretization uniform_time(0.0, .05, 10);
    std::vector<size_t> indexes(uniform_time.get_nb_points());
    for (size_t i = 0; i < uniform_time.get_nb_points(); i++) indexes[i] = i;
    for (double i = uniform_time.get_end(); i >= uniform_time.get_start();
         i -= .001)
        if (uniform_time.iteration(i) == indexes.back()) indexes.pop_back();
    ASSERT_TRUE(indexes.empty());
}

TEST(TimeDiscretizationTest, ReverseTimeDiscretization) {
    ASSERT_THROW(time_discretization::UniformTimeDiscretization uniform_time(
                     10.0, 0.0, 10),
                 std::invalid_argument);
    ASSERT_THROW(time_discretization::UniformTimeDiscretization uniform_time(
                     -1.0, 0.0, 10),
                 std::invalid_argument);
    ASSERT_THROW(
        time_discretization::UniformTimeDiscretization uniform_time(.0, .5, 0),
        std::invalid_argument);

    ASSERT_THROW(time_discretization::UniformTimeDiscretization uniform_time(
                     .0, .5, -10),
                 std::invalid_argument);
}