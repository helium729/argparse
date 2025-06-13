# argparse

This is a library for parsing command line arguments. It is designed to be
simple and easy to use. It is also designed to be extensible, additional 
types can be added to the library.

The library can be linked as a static library in any platform with a C++ compiler and 
C++ STL support. 

## Compilation

For Linux/MSYS2, the following commands can be used to compile the library:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<your prefix>
make -j4
make install
```

For development and testing, use Debug build type:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4
```

For other platforms, the library can be compiled using CMake and corresponding build system.

## Testing

The library includes a comprehensive test suite with 44 test cases covering all functionality:

### Running Tests

After building the library, run the test suite using:

```bash
# Run all tests with CTest
ctest --verbose

# Or use the custom target
make run_tests

# Run individual test suites
./test_parser      # Parser functionality tests (17 tests)
./test_parameters  # Parameter type tests (12 tests)
./test_util        # Utility function tests (8 tests)
./test_integration # Integration tests (7 tests)
```

### Test Coverage

The test suite covers:

- **Parser Tests**: Constructor/destructor, parameter addition, flag parsing, value retrieval, error handling, help generation
- **Parameter Tests**: All parameter types (NONE, INTEGER, STRING, FLOAT), required parameters, edge cases
- **Utility Tests**: Parameter factory functions, memory management, default behaviors
- **Integration Tests**: Complex real-world scenarios, mixed parameter usage, comprehensive error handling

All tests pass with 100% success rate, ensuring reliable functionality across all supported use cases.

## Usage

### Basic Example

```cpp
#include "argparse/parser.h"
#include <iostream>

int main(int argc, char** argv) {
    argparse::parser parser;
    
    // Add parameters
    parser.add_parameter("h", "help", "Show help message", argparse::parameter_type::NONE);
    parser.add_parameter("v", "verbose", "Enable verbose output", argparse::parameter_type::NONE);
    parser.add_parameter("f", "file", "Input file path", argparse::parameter_type::STRING);
    parser.add_parameter("n", "number", "Number of iterations", argparse::parameter_type::INTEGER);
    
    // Parse command line
    parser.parse(argc, argv);
    
    // Check for help
    bool help = false;
    if (parser.get_parameter_value_to("help", &help) && help) {
        std::cout << parser.get_help_message() << std::endl;
        return 0;
    }
    
    // Get parameter values
    bool verbose = false;
    parser.get_parameter_value_to("verbose", &verbose);
    
    std::string filename;
    parser.get_parameter_value_to("file", &filename);
    
    int iterations = 1;
    parser.get_parameter_value_to("number", &iterations);
    
    // Use parsed values
    if (verbose) {
        std::cout << "Processing " << filename << " with " << iterations << " iterations" << std::endl;
    }
    
    return 0;
}
```

### Supported Parameter Types

- `NONE`: Boolean flags (presence indicates true)
- `STRING`: String values
- `INTEGER`: Integer values (supports decimal, hexadecimal, octal)
- `FLOAT`: Floating-point values

### Additional Examples

See `example/src/example.cc` for a basic usage example, or refer to the comprehensive test suite in the `tests/` directory for advanced usage patterns.

For more complex usage examples, see main.cc in [scatk](https://github.com/helium729/scatk).

