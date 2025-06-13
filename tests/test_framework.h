#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>

// Simple test framework macros
#define ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "ASSERTION FAILED: " << #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_FALSE(condition) \
    do { \
        if ((condition)) { \
            std::cerr << "ASSERTION FAILED: " << #condition << " should be false at " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::cerr << "ASSERTION FAILED: Expected " << (expected) << " but got " << (actual) << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while(0)

#define ASSERT_STREQ(expected, actual) \
    do { \
        if (std::string(expected) != std::string(actual)) { \
            std::cerr << "ASSERTION FAILED: Expected \"" << (expected) << "\" but got \"" << (actual) << "\" at " << __FILE__ << ":" << __LINE__ << std::endl; \
            return false; \
        } \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        std::cout << "Running " << #test_func << "... "; \
        if (test_func()) { \
            std::cout << "PASSED" << std::endl; \
            tests_passed++; \
        } else { \
            std::cout << "FAILED" << std::endl; \
            tests_failed++; \
        } \
        tests_total++; \
    } while(0)

// Test result tracking
extern int tests_total;
extern int tests_passed;
extern int tests_failed;

void print_test_summary();

#endif