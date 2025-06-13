# cmake version
cmake_minimum_required(VERSION 3.0)

# project name
project(argparse)

# search for source files
file(GLOB_RECURSE SOURCES "src/*.cc")

# search for header files
file(GLOB_RECURSE HEADERS "include/*.h")

# include directories
include_directories(include)

# combine source and header files
set(SOURCES ${SOURCES} ${HEADERS})

# add library
add_library(argparse STATIC ${SOURCES})

# install
install(TARGETS argparse DESTINATION lib)
# install headers
install(DIRECTORY include/argparse DESTINATION include)

# Enable testing
enable_testing()

# Add test framework
add_library(test_framework tests/test_framework.cc tests/test_framework.h)
target_include_directories(test_framework PUBLIC tests)

# Add individual test executables
add_executable(test_parser tests/test_parser.cc)
target_link_libraries(test_parser argparse test_framework)
add_test(NAME test_parser COMMAND test_parser)

add_executable(test_parameters tests/test_parameters.cc)
target_link_libraries(test_parameters argparse test_framework)
add_test(NAME test_parameters COMMAND test_parameters)

add_executable(test_util tests/test_util.cc)
target_link_libraries(test_util argparse test_framework)
add_test(NAME test_util COMMAND test_util)

add_executable(test_integration tests/test_integration.cc)
target_link_libraries(test_integration argparse test_framework)
add_test(NAME test_integration COMMAND test_integration)

# Add test runner
add_executable(test_runner tests/test_runner.cc)
target_link_libraries(test_runner test_framework)

# Add a custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS test_parser test_parameters test_util test_integration
    COMMENT "Running all tests"
)

