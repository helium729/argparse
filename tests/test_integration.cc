#include "test_framework.h"
#include "argparse/parser.h"
#include <vector>
#include <string>

using namespace argparse;

// Test realistic command line parsing scenario
bool test_integration_complex_parsing() {
    parser p;
    
    // Add various parameter types
    p.add_parameter("h", "help", "Show help message", NONE, false);
    p.add_parameter("v", "verbose", "Enable verbose output", NONE, false);
    p.add_parameter("f", "file", "Input file path", STRING, true, ""); // Required
    p.add_parameter("o", "output", "Output file path", STRING, false, "output.txt");
    p.add_parameter("c", "count", "Number of iterations", INTEGER, false, "10");
    p.add_parameter("r", "rate", "Processing rate", FLOAT, false, "1.0");
    p.add_parameter("t", "threads", "Number of threads", INTEGER, false, "1");
    
    // Test comprehensive argument parsing
    std::vector<std::string> args = {
        "myprogram",
        "--help",
        "-v",
        "--file", "input.txt",
        "-o", "result.txt",
        "--count", "50",
        "--rate", "2.5",
        "-t", "4"
    };
    
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    // Verify all values were parsed correctly
    bool help_value = false;
    ASSERT_TRUE(p.get_parameter_value_to("help", &help_value));
    ASSERT_TRUE(help_value);
    
    bool verbose_value = false;
    ASSERT_TRUE(p.get_parameter_value_to("v", &verbose_value));
    ASSERT_TRUE(verbose_value);
    
    std::string file_value;
    ASSERT_TRUE(p.get_parameter_value_to("file", &file_value));
    ASSERT_STREQ("input.txt", file_value);
    
    std::string output_value;
    ASSERT_TRUE(p.get_parameter_value_to("o", &output_value));
    ASSERT_STREQ("result.txt", output_value);
    
    i64 count_value;
    ASSERT_TRUE(p.get_parameter_value_to("count", &count_value));
    ASSERT_EQ(50, count_value);
    
    f64 rate_value;
    ASSERT_TRUE(p.get_parameter_value_to("rate", &rate_value));
    ASSERT_EQ(2.5, rate_value);
    
    i64 threads_value;
    ASSERT_TRUE(p.get_parameter_value_to("t", &threads_value));
    ASSERT_EQ(4, threads_value);
    
    return true;
}

// Test mixed short and long parameter usage
bool test_integration_mixed_parameters() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    p.add_parameter("n", "number", "A number", INTEGER, false, "0");
    p.add_parameter("v", "verbose", "Verbose mode", NONE, false);
    
    // Mix short and long names
    std::vector<std::string> args = {
        "program",
        "-f", "short_file.txt",
        "--number", "123",
        "-v"
    };
    
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    std::string file_value;
    ASSERT_TRUE(p.get_parameter_value_to("f", &file_value));
    ASSERT_STREQ("short_file.txt", file_value);
    
    i64 number_value;
    ASSERT_TRUE(p.get_parameter_value_to("number", &number_value));
    ASSERT_EQ(123, number_value);
    
    bool verbose_value = false;
    ASSERT_TRUE(p.get_parameter_value_to("v", &verbose_value));
    ASSERT_TRUE(verbose_value);
    
    return true;
}

// Test default values
bool test_integration_default_values() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default_file.txt");
    p.add_parameter("n", "number", "A number", INTEGER, false, "42");
    p.add_parameter("r", "rate", "A rate", FLOAT, false, "3.14");
    p.add_parameter("v", "verbose", "Verbose mode", NONE, false);
    
    // Parse with no arguments (except program name)
    std::vector<std::string> args = {"program"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    // Check that default values are accessible
    std::string file_value;
    ASSERT_TRUE(p.get_parameter_value_to("f", &file_value));
    ASSERT_STREQ("default_file.txt", file_value);
    
    i64 number_value;
    ASSERT_TRUE(p.get_parameter_value_to("n", &number_value));
    ASSERT_EQ(42, number_value);
    
    f64 rate_value;
    ASSERT_TRUE(p.get_parameter_value_to("r", &rate_value));
    ASSERT_EQ(3.14, rate_value);
    
    // Verbose should be false (not set)
    bool verbose_value = true; // Start with true to ensure it gets set to false
    ASSERT_TRUE(p.get_parameter_value_to("v", &verbose_value));
    ASSERT_FALSE(verbose_value);
    
    return true;
}

// Test help message formatting
bool test_integration_help_message_format() {
    parser p;
    p.add_parameter("h", "help", "Show this help message", NONE, false);
    p.add_parameter("v", "verbose", "Enable verbose output", NONE, false);
    p.add_parameter("f", "file", "Specify input file", STRING, false, "input.txt");
    p.add_parameter("", "output-only", "Output only parameter", STRING, false, "");
    p.add_parameter("x", "", "Short only parameter", NONE, false);
    
    // Parse to set program name
    std::vector<std::string> args = {"myapp"};
    p.parse(args);
    
    std::string help_msg = p.get_help_message();
    
    // Check for basic structure
    ASSERT_TRUE(help_msg.find("Usage: myapp [options]") != std::string::npos);
    
    // Check that all parameters appear
    ASSERT_TRUE(help_msg.find("-h, --help") != std::string::npos);
    ASSERT_TRUE(help_msg.find("Show this help message") != std::string::npos);
    ASSERT_TRUE(help_msg.find("-v, --verbose") != std::string::npos);
    ASSERT_TRUE(help_msg.find("-f, --file") != std::string::npos);
    ASSERT_TRUE(help_msg.find("--output-only") != std::string::npos);
    ASSERT_TRUE(help_msg.find("-x") != std::string::npos);
    
    return true;
}

// Test error scenarios in integration
bool test_integration_error_scenarios() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "");
    p.add_parameter("n", "number", "A number", INTEGER, false, "0");
    
    // Test unknown parameter error
    std::vector<std::string> args1 = {"program", "--unknown"};
    ASSERT_FALSE(p.parse(args1));
    
    // Test missing value error
    std::vector<std::string> args2 = {"program", "-f"};
    ASSERT_FALSE(p.parse(args2));
    
    // Test missing value with another flag following
    std::vector<std::string> args3 = {"program", "-f", "-n", "123"};
    ASSERT_FALSE(p.parse(args3)); // -f should require a value, -n is interpreted as the value
    
    return true;
}

// Test program name extraction from path
bool test_integration_program_name_extraction() {
    parser p;
    p.add_parameter("h", "help", "Show help", NONE, false);
    
    // Test with full path
    std::vector<std::string> args1 = {"/usr/bin/myprogram", "-h"};
    p.parse(args1);
    std::string help1 = p.get_help_message();
    ASSERT_TRUE(help1.find("Usage: myprogram [options]") != std::string::npos);
    
    // Test with Windows-style path
    std::vector<std::string> args2 = {"C:\\Program Files\\myapp.exe", "-h"};
    p.parse(args2);
    std::string help3 = p.get_help_message();
    ASSERT_TRUE(help3.find("Usage: myapp.exe [options]") != std::string::npos);
    
    // Test with relative path
    std::vector<std::string> args3 = {"./bin/myapp", "-h"};
    p.parse(args3);
    std::string help2 = p.get_help_message();
    ASSERT_TRUE(help2.find("Usage: myapp [options]") != std::string::npos);
    
    return true;
}

// Test edge cases
bool test_integration_edge_cases() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "");
    
    // Test empty program name handling (shouldn't crash)
    std::vector<std::string> args1 = {"", "-f", "test.txt"};
    bool result1 = p.parse(args1);
    ASSERT_TRUE(result1);
    
    // Test single character arguments
    std::vector<std::string> args2 = {"p", "-f", "a"};
    bool result2 = p.parse(args2);
    ASSERT_TRUE(result2);
    
    std::string file_value;
    ASSERT_TRUE(p.get_parameter_value_to("f", &file_value));
    ASSERT_STREQ("a", file_value);
    
    return true;
}

// Main test runner
int main() {
    std::cout << "Running integration tests..." << std::endl;
    
    RUN_TEST(test_integration_complex_parsing);
    RUN_TEST(test_integration_mixed_parameters);
    RUN_TEST(test_integration_default_values);
    RUN_TEST(test_integration_help_message_format);
    RUN_TEST(test_integration_error_scenarios);
    RUN_TEST(test_integration_program_name_extraction);
    RUN_TEST(test_integration_edge_cases);
    
    print_test_summary();
    
    return tests_failed > 0 ? 1 : 0;
}