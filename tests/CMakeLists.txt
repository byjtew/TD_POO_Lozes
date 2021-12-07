
find_package(GTest REQUIRED)

add_executable(Equation_test Equation_test.cpp)
set_target_properties(Equation_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
target_link_libraries(Equation_test  GTest::gtest GTest::Main Problem Equation TimeDiscretization Variable)
enable_testing()
include(GoogleTest)
gtest_discover_tests(Equation_test)

add_executable(Variable_test Variable_test.cpp)
set_target_properties(Variable_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
target_link_libraries(Variable_test  GTest::gtest GTest::Main Problem Equation TimeDiscretization Variable)
enable_testing()
include(GoogleTest)
gtest_discover_tests(Variable_test)

add_executable(TimeDiscretization_test TimeDiscretization_test.cpp)
set_target_properties(TimeDiscretization_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
target_link_libraries(TimeDiscretization_test  GTest::gtest GTest::Main Problem Equation TimeDiscretization Variable)
enable_testing()
include(GoogleTest)
gtest_discover_tests(TimeDiscretization_test)