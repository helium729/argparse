#include "test_framework.h"

int tests_total = 0;
int tests_passed = 0;
int tests_failed = 0;

void print_test_summary() {
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "Total tests: " << tests_total << std::endl;
    std::cout << "Passed: " << tests_passed << std::endl;
    std::cout << "Failed: " << tests_failed << std::endl;
    std::cout << "Success rate: " << (tests_total > 0 ? (tests_passed * 100.0 / tests_total) : 0) << "%" << std::endl;
}