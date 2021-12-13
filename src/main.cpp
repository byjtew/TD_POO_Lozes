#include <unistd.h>
#include <thread>
#include <iostream>
#include <vector>

#include "Equation.hpp"
#include "Problem.hpp"
#include "TimeDiscretization.hpp"
#include "Variable.hpp"

int main(int argc, char const *argv[]) {
    std::thread first_thread([](){
        return 0;
    });

    first_thread.join();
    return 0;
}
