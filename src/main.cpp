#include <unistd.h>

#include <iostream>
#include <vector>

#include "Equation.hpp"
#include "Problem.hpp"
#include "TimeDiscretization.hpp"
#include "Variable.hpp"

// Defined by CMake [ DEFAULT: 1 ]
// Usage for release: cmake <target> -DCMAKE_BUILD_TYPE=Release
#if !defined(DEBUG_MODE)
#define DEBUG_MODE 1
#endif  // DEBUG_MODE

int main(int argc, char const *argv[]) {
    return 0;
}
