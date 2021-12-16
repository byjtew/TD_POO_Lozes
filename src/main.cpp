#include <math.h>
#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

#include "Equation.hpp"
#include "Problem.hpp"
#include "TimeDiscretization.hpp"
#include "Timer.hpp"
#include "Variable.hpp"

template <class Integrator_A, class Integrator_B>
void testSolvingParallel(time_discretization::ITimeDiscretization *time,
                         std::function<double(double)> f, double exact_result) {
    equation::Equation eq(f);
    problem::Problem problem_A(eq, time), problem_B(eq, time);
    std::pair<timer::Timer, timer::Timer> timers(timer::Timer{}, timer::Timer{});

    auto results = problem::Problem::solve_parallel<Integrator_A, Integrator_B>(
        problem_A, problem_B, timers);

    std::cout
        << "-- Solving problem_A result comapred to the correct result is: |"
        << exact_result << " - " << results.first.getLast()
        << "| = " << std::fabs(exact_result - results.first.getLast()) << " --"
        << std::endl;
    std::cout << "-- Solving of problem_A took "
              << timers.first.printInSeconds() << " seconds --" << std::endl;

    std::cout
        << "-- Solving problem_B result comapred to the correct result is: |"
        << exact_result << " - " << results.second.getLast()
        << "| = " << std::fabs(exact_result - results.second.getLast()) << " --"
        << std::endl;
    std::cout << "-- Solving of problem_B took "
              << timers.second.printInSeconds() << " seconds --" << std::endl;
}

int main(int argc, char const *argv[]) {
    time_discretization::UniformTimeDiscretization unif_time(0, 10, 1e5);
    testSolvingParallel<equation::integrations::EulerIntegration,
                        equation::integrations::RungeKuttaIntegration>(
        &unif_time, [](double x) { return x; }, 10);

    return 0;
}
