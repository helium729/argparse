# Argparse Unit Tests

This directory contains comprehensive unit tests for the argparse library.

## Test Structure

- `test_framework.h/cc` - Simple test framework with assertion macros
- `test_parser.cc` - Tests for the main parser class functionality
- `test_parameters.cc` - Tests for all parameter types (none, integer, string, float)
- `test_util.cc` - Tests for the utility factory class
- `test_integration.cc` - Integration tests for complex scenarios
- `test_runner.cc` - Main test runner (optional, use ctest instead)

## Running Tests

### Build and Run All Tests
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
ctest --verbose
```

### Run Individual Test Suites
```bash
./test_parser        # Parser functionality tests
./test_parameters    # Parameter class tests  
./test_util          # Utility class tests
./test_integration   # Integration tests
```

### Use CMake Test Target
```bash
make run_tests
```

## Test Coverage

The tests cover:

### Parser Class (`test_parser.cc`)
- Constructor/destructor
- Adding parameters of all types
- Parsing short flags (-h)
- Parsing long flags (--help)
- Parsing parameters with values
- Multiple parameter parsing
- argc/argv interface
- Error handling (unknown parameters, missing values)
- Help message generation
- Parameter value retrieval

### Parameter Classes (`test_parameters.cc`)
- parameter_none: Boolean flags
- parameter_integer: Integer parsing with different bases
- parameter_string: String parameter handling
- parameter_float: Floating-point parsing
- Required parameter functionality
- Parameter construction and data retrieval

### Utility Class (`test_util.cc`)
- Parameter factory creation for all types
- Parameter functionality verification
- Memory management (proper construction/destruction)

### Integration Tests (`test_integration.cc`)
- Complex real-world parsing scenarios
- Mixed short/long parameter usage
- Default value handling
- Help message formatting
- Error scenario handling
- Program name extraction from paths
- Edge cases and boundary conditions

## Test Results

All 44 individual test cases pass (100% success rate):
- Parser tests: 17/17 passed
- Parameter tests: 12/12 passed  
- Util tests: 8/8 passed
- Integration tests: 7/7 passed