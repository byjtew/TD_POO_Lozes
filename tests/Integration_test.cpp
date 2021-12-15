

#include <gtest/gtest.h>

#include "Equation.hpp"
#include "Problem.hpp"
#include "TimeDiscretization.hpp"
#include "Timer.hpp"
#include "Variable.hpp"

TEST(IntegrationTest, Euler_vs_RungeKutta) {
    equation::Equation eq([](double x) { return 2 * x; });  // (x^2)'
    time_discretization::UniformTimeDiscretization unif(0, 100, 1e7);
    problem::Problem problem_A(eq, &unif), problem_B(eq, &unif);
    timer::Timer timer_a{}, timer_b{};
    std::pair<timer::Timer, timer::Timer> timers_pair(timer_a, timer_b);
    auto results_pair = problem::Problem::solve_parallel<
        equation::integrations::EulerIntegration,
        equation::integrations::RungeKuttaIntegration>(problem_A, problem_B,
                                                       timers_pair);
    ASSERT_EQ(results_pair.first.getLast(), results_pair.second.getLast());
}
