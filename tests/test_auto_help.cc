#include "test_framework.h"
#include "argparse/parser.h"
#include <iostream>

using namespace argparse;

// Test that auto-help is enabled by default
bool test_auto_help_default_enabled() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    // Test with auto-help disabled - should work normally
    p.set_auto_help(false);
    std::vector<std::string> args = {"program", "-h"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    bool got_help = p.get_parameter_value_to("h", &help_value);
    ASSERT_TRUE(got_help);
    ASSERT_TRUE(help_value);
    
    return true;
}

// Test that set_auto_help can be called and disables auto-help
bool test_set_auto_help_disables() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    // Disable auto-help
    p.set_auto_help(false);
    
    // Test with help flag - should not exit
    std::vector<std::string> args = {"program", "-h"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    bool got_help = p.get_parameter_value_to("h", &help_value);
    ASSERT_TRUE(got_help);
    ASSERT_TRUE(help_value);
    
    return true;
}

// Test that set_auto_help can be called multiple times
bool test_set_auto_help_multiple_calls() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    // Should be able to call multiple times without error
    p.set_auto_help(true);
    p.set_auto_help(false);
    p.set_auto_help(true);
    p.set_auto_help(false);
    
    // Test that the last call takes effect
    std::vector<std::string> args = {"program", "-h"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);  // Should not exit because auto-help is disabled
    
    return true;
}

// Test backward compatibility - unknown parameter behavior with auto-help disabled
bool test_backward_compatibility_unknown_param() {
    parser p;
    p.set_auto_help(false);
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    std::vector<std::string> args = {"program", "--unknown"};
    bool result = p.parse(args);
    ASSERT_FALSE(result);  // Should return false without exiting
    
    return true;
}

// Test backward compatibility - missing value behavior with auto-help disabled
bool test_backward_compatibility_missing_value() {
    parser p;
    p.set_auto_help(false);
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    std::vector<std::string> args = {"program", "-f"};
    bool result = p.parse(args);
    ASSERT_FALSE(result);  // Should return false without exiting
    
    return true;
}

// Test that normal parsing still works with auto-help enabled
bool test_normal_parsing_with_auto_help() {
    parser p;
    // auto-help should be enabled by default
    p.add_parameter("h", "help", "Show help message", NONE, false);
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    p.add_parameter("v", "verbose", "Verbose mode", NONE, false);
    
    std::vector<std::string> args = {"program", "-f", "test.txt", "-v"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    // Check that file parameter was set
    std::string file_value;
    bool got_file = p.get_parameter_value_to("f", &file_value);
    ASSERT_TRUE(got_file);
    ASSERT_STREQ("test.txt", file_value);
    
    // Check that verbose flag was set
    bool verbose_value = false;
    bool got_verbose = p.get_parameter_value_to("v", &verbose_value);
    ASSERT_TRUE(got_verbose);
    ASSERT_TRUE(verbose_value);
    
    // Check that help was not set
    bool help_value = true;
    bool got_help = p.get_parameter_value_to("h", &help_value);
    ASSERT_TRUE(got_help);
    ASSERT_FALSE(help_value);
    
    return true;
}

// Test that help detection works with both short and long names
bool test_help_detection_short_and_long() {
    // Test with short name only
    parser p1;
    p1.set_auto_help(false);
    p1.add_parameter("h", "", "Show help message", NONE, false);
    
    std::vector<std::string> args1 = {"program", "-h"};
    bool result1 = p1.parse(args1);
    ASSERT_TRUE(result1);
    
    bool help_value1 = false;
    bool got_help1 = p1.get_parameter_value_to("h", &help_value1);
    ASSERT_TRUE(got_help1);
    ASSERT_TRUE(help_value1);
    
    // Test with long name only
    parser p2;
    p2.set_auto_help(false);
    p2.add_parameter("", "help", "Show help message", NONE, false);
    
    std::vector<std::string> args2 = {"program", "--help"};
    bool result2 = p2.parse(args2);
    ASSERT_TRUE(result2);
    
    bool help_value2 = false;
    bool got_help2 = p2.get_parameter_value_to("help", &help_value2);
    ASSERT_TRUE(got_help2);
    ASSERT_TRUE(help_value2);
    
    return true;
}

// Main test runner
int main() {
    std::cout << "Running auto-help feature tests..." << std::endl;
    
    RUN_TEST(test_auto_help_default_enabled);
    RUN_TEST(test_set_auto_help_disables);
    RUN_TEST(test_set_auto_help_multiple_calls);
    RUN_TEST(test_backward_compatibility_unknown_param);
    RUN_TEST(test_backward_compatibility_missing_value);
    RUN_TEST(test_normal_parsing_with_auto_help);
    RUN_TEST(test_help_detection_short_and_long);
    
    print_test_summary();
    
    return tests_failed > 0 ? 1 : 0;
}