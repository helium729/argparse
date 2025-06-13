#include "test_framework.h"
#include <iostream>
#include <cstdlib>

// Forward declarations for test runners
int run_parser_tests();
int run_parameter_tests();
int run_util_tests();
int run_integration_tests();

int main() {
    std::cout << "=== Running All Argparse Unit Tests ===" << std::endl;
    
    int total_failures = 0;
    
    std::cout << "\n1. Parser Tests:" << std::endl;
    total_failures += run_parser_tests();
    
    std::cout << "\n2. Parameter Tests:" << std::endl;
    total_failures += run_parameter_tests();
    
    std::cout << "\n3. Util Tests:" << std::endl;
    total_failures += run_util_tests();
    
    std::cout << "\n4. Integration Tests:" << std::endl;
    total_failures += run_integration_tests();
    
    std::cout << "\n=== Overall Test Summary ===" << std::endl;
    if (total_failures == 0) {
        std::cout << "All tests PASSED!" << std::endl;
        return 0;
    } else {
        std::cout << "Tests FAILED with " << total_failures << " test suites failing." << std::endl;
        return 1;
    }
}

// Stub implementations that would call the individual test programs
// In a real implementation, these might fork/exec the test programs
// or include the test functions directly

int run_parser_tests() {
    std::cout << "Running parser tests via system call..." << std::endl;
    return system("./test_parser");
}

int run_parameter_tests() {
    std::cout << "Running parameter tests via system call..." << std::endl;
    return system("./test_parameters");
}

int run_util_tests() {
    std::cout << "Running util tests via system call..." << std::endl;
    return system("./test_util");
}

int run_integration_tests() {
    std::cout << "Running integration tests via system call..." << std::endl;
    return system("./test_integration");
}