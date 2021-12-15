
find_package(GTest REQUIRED)

add_executable(Integration_test Integration_test.cpp)
set_target_properties(Integration_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
target_link_libraries(Integration_test  GTest::GTest GTest::Main Problem Equation TimeDiscretization Variable Timer)
enable_testing()
include(GoogleTest)
gtest_discover_tests(Integration_test)
