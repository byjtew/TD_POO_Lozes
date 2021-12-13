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

int main(int argc, char const *argv[]) {
    time_discretization::UniformTimeDiscretization unif_time(0, 100, 1e6);
    equation::Equation eq0([](double x) { return 1; });
    problem::Problem problem0(eq0, &unif_time);
    double true_result = 100;
    variable::Variable results0(&unif_time);

    timer::Timer timer0{};

    std::thread first_thread([&problem0, &results0, &timer0]() {
        timer0.start();
        results0 = problem0.solve();
        timer0.stop();
    });

    first_thread.join();
    std::cout << "-- Solving took " << timer0.printInSeconds() << " seconds --"
              << std::endl;

    std::cout << "-- Solving difference with the correct result is: |"
              << true_result << " - " << results0.getLast() << "| = "
              << std::fabs(true_result - results0.getLast()) << " --"
              << std::endl;

    return 0;
}
