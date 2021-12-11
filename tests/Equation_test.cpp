#include "Equation.hpp"

#include <gtest/gtest.h>

#include "Problem.hpp"
#include "TimeDiscretization.hpp"
#include "Variable.hpp"

TEST(EquationTest, VariableLength) {
    equation::Equation eq([](double x) { return x; });
    time_discretization::UniformTimeDiscretization unif(0, 10, 100);
    variable::Variable results = problem::Problem(eq, &unif).solve("equation_test.dat");
    ASSERT_EQ(results.size(), unif.get_nb_points());
}
