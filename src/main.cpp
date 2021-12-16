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
void testSolvingConcurrent(time_discretization::ITimeDiscretization *time,
                           std::function<double(double)> f,
                           double exact_result) {
    std::cout << "\n--- Solving problems in concurrent mode ---" << std::endl;
    std::cout << "\n-- Discretization of " << time->get_nb_points()
              << " points--\n"
              << std::endl;
    equation::Equation eq(f);
    timer::Timer timer{};

    timer.start();
    auto results =
        problem::Problem::solve_concurrent<Integrator_A, Integrator_B>(eq, eq,
                                                                       time);
    timer.stop();

    std::cout
        << "-- Solving problem_A result compared to the correct result is: |"
        << exact_result << " - " << results.first.getLast()
        << "| = " << std::fabs(exact_result - results.first.getLast()) << " --"
        << std::endl;

    std::cout
        << "-- Solving problem_B result compared to the correct result is: |"
        << exact_result << " - " << results.second.getLast()
        << "| = " << std::fabs(exact_result - results.second.getLast()) << " --"
        << std::endl;
    std::cout << "\n-- Solving of problems in concurrent mode took "
              << timer.printInSeconds() << " seconds --" << std::endl;
    std::cout << "\n--- End of the solving ---\n" << std::endl;
}

template <class Integrator_A, class Integrator_B>
void testSolvingParallel(time_discretization::ITimeDiscretization *time,
                         std::function<double(double)> f, double exact_result) {
    std::cout << "\n--- Solving problems in parallel mode ---" << std::endl;
    std::cout << "\n-- Discretization of " << time->get_nb_points()
              << " points--\n"
              << std::endl;
    equation::Equation eq(f);
    problem::Problem problem_A(eq, time), problem_B(eq, time);
    std::pair<timer::Timer, timer::Timer> timers(timer::Timer{},
                                                 timer::Timer{});

    auto results = problem::Problem::solve_parallel<Integrator_A, Integrator_B>(
        problem_A, problem_B, timers);

    std::cout
        << "-- Solving problem_A result compared to the correct result is: |"
        << exact_result << " - " << results.first.getLast()
        << "| = " << std::fabs(exact_result - results.first.getLast()) << " --"
        << std::endl;
    std::cout << "-- Solving of problem_A in parallel mode took "
              << timers.first.printInSeconds() << " seconds --" << std::endl;

    std::cout
        << "\n-- Solving problem_B result compared to the correct result is: |"
        << exact_result << " - " << results.second.getLast()
        << "| = " << std::fabs(exact_result - results.second.getLast()) << " --"
        << std::endl;
    std::cout << "-- Solving of problem_B in parallel mode took "
              << timers.second.printInSeconds() << " seconds --" << std::endl;

    double accumulator = .0;
    std::cout << "\n--- End of the solving ---\n" << std::endl;
}

int main(int argc, char const *argv[]) {
    time_discretization::UniformTimeDiscretization unif_time(0, 20, 1e5);

    testSolvingParallel<equation::integrations::EulerIntegration,
                        equation::integrations::RungeKuttaIntegration>(
        &unif_time, [](double x) { return x * log10f64(x); },
        20 * log10f64(20));

    testSolvingConcurrent<equation::integrations::EulerIntegration,
                          equation::integrations::RungeKuttaIntegration>(
        &unif_time, [](double x) { return x * log10f64(x); },
        20 * log10f64(20));
    return 0;
}
