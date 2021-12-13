cmake_minimum_required(VERSION 3.16)
project(equation)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

#cmake <target> -DCMAKE_BUILD_TYPE=Release
if(${DCMAKE_BUILD_TYPE}|"Not specified" STREQUAL "Release")
    message("Release build")
    add_compile_definitions(DEBUG_MODE=0)
else()
    message("Debug build")
    add_compile_definitions(DEBUG_MODE=1)
endif()

include_directories(src)
add_subdirectory(src)

add_subdirectory(tests)

#add_test('' tests/equation_test.cpp)