add_library(Problem STATIC Problem.cpp Problem.hpp)
add_library(Equation STATIC Equation.cpp Equation.hpp)
add_library(TimeDiscretization STATIC TimeDiscretization.cpp TimeDiscretization.hpp)
add_library(Variable STATIC Variable.cpp Variable.hpp)
add_library(Timer STATIC Timer.cpp Timer.hpp)


add_executable(main main.cpp)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Threads)
target_link_libraries(main PUBLIC Threads::Threads Problem Equation TimeDiscretization Variable Timer)