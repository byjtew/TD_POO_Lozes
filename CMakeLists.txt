cmake_minimum_required(VERSION 3.16)
project(equation)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

if(${CMAKE_BUILD_TYPE} && ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("Debug build")
    add_compile_definitions(DEBUG_MODE=1)
else()
    message("Not debug build")
    add_compile_definitions(DEBUG_MODE=0)
endif()

include_directories(src)
add_subdirectory(src)

add_subdirectory(tests)

#add_test('' tests/equation_test.cpp)