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

The library includes a comprehensive test suite with 51 test cases covering all functionality:

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
./test_auto_help   # Auto-help feature tests (7 tests)
```

### Test Coverage

The test suite covers:

- **Parser Tests**: Constructor/destructor, parameter addition, flag parsing, value retrieval, error handling, help generation
- **Parameter Tests**: All parameter types (NONE, INTEGER, STRING, FLOAT), required parameters, edge cases
- **Utility Tests**: Parameter factory functions, memory management, default behaviors
- **Integration Tests**: Complex real-world scenarios, mixed parameter usage, comprehensive error handling
- **Auto-Help Tests**: Automatic help display, backward compatibility, configuration options

All tests pass with 100% success rate, ensuring reliable functionality across all supported use cases.

## Usage

### Auto-Help Feature (Default Behavior)

The library now includes automatic help handling enabled by default. This provides a simplified, more user-friendly experience:

- **Automatic help display**: When `-h` or `--help` is provided, help is automatically printed and the program exits
- **Automatic error handling**: When parsing fails (unknown parameters, missing values, etc.), an error message and help are automatically displayed, then the program exits
- **Zero boilerplate**: No manual help checking or error handling required

#### Simple Auto-Help Example

```cpp
#include "argparse/parser.h"
#include <iostream>

int main(int argc, char** argv) {
    argparse::parser parser;
    
    // Add parameters
    parser.add_parameter("h", "help", "Show help message", argparse::parameter_type::NONE);
    parser.add_parameter("f", "file", "Input file path", argparse::parameter_type::STRING);
    parser.add_parameter("v", "verbose", "Enable verbose output", argparse::parameter_type::NONE);
    
    // Parse automatically handles help and errors
    parser.parse(argc, argv);
    
    // Get parameter values (only reached if parsing successful)
    std::string filename;
    parser.get_parameter_value_to("file", &filename);
    
    bool verbose = false;
    parser.get_parameter_value_to("verbose", &verbose);
    
    // Use parsed values
    if (verbose) {
        std::cout << "Processing file: " << filename << std::endl;
    }
    
    return 0;
}
```

**Command line behavior:**
```bash
$ ./app --help
Usage: app [options]
-f, --file    Input file path
-h, --help    Show help message  
-v, --verbose Enable verbose output

$ ./app --unknown
error: unknown parameter unknown
Usage: app [options]
-f, --file    Input file path
-h, --help    Show help message
-v, --verbose Enable verbose output
```

### Backward Compatibility

For existing code that needs manual control over help and error handling, use `set_auto_help(false)`:

```cpp
argparse::parser parser;
parser.set_auto_help(false);  // Disable auto-help for manual control

// ... add parameters ...

if (!parser.parse(argc, argv)) {
    std::cerr << "Parse failed!" << std::endl;
    std::cout << parser.get_help_message() << std::endl;
    return 1;
}

// Manual help checking
bool help = false;
if (parser.get_parameter_value_to("help", &help) && help) {
    std::cout << parser.get_help_message() << std::endl;
    return 0;
}
```

### Basic Example

### Basic Example (Legacy Manual Approach)

For comparison, here's how you would handle help manually with `set_auto_help(false)`:

```cpp
#include "argparse/parser.h"
#include <iostream>

int main(int argc, char** argv) {
    argparse::parser parser;
    parser.set_auto_help(false);  // Disable auto-help for manual control
    
    // Add parameters
    parser.add_parameter("h", "help", "Show help message", argparse::parameter_type::NONE);
    parser.add_parameter("v", "verbose", "Enable verbose output", argparse::parameter_type::NONE);
    parser.add_parameter("f", "file", "Input file path", argparse::parameter_type::STRING);
    parser.add_parameter("n", "number", "Number of iterations", argparse::parameter_type::INTEGER);
    
    // Parse command line
    if (!parser.parse(argc, argv)) {
        std::cerr << "Failed to parse arguments!" << std::endl;
        std::cout << parser.get_help_message() << std::endl;
        return 1;
    }
    
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

The `example/` directory contains demonstration programs:

- `example_auto_help.cc`: Shows the new default auto-help behavior  
- `example_manual_help.cc`: Shows backward-compatible manual help handling
- Basic usage patterns can also be found in `example/src/example.cc`

For comprehensive usage patterns, refer to the test suite in the `tests/` directory.

For more complex usage examples, see main.cc in [scatk](https://github.com/helium729/scatk).

