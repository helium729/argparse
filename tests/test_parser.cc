#include "test_framework.h"
#include "argparse/parser.h"
#include <vector>
#include <string>

using namespace argparse;

// Test parser construction and destruction
bool test_parser_construction() {
    parser p;
    return true; // If we get here, construction worked
}

// Test adding parameters
bool test_add_parameter_none() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    return true;
}

bool test_add_parameter_string() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    return true;
}

bool test_add_parameter_integer() {
    parser p;
    p.add_parameter("n", "number", "A number", INTEGER, false, "42");
    return true;
}

bool test_add_parameter_float() {
    parser p;
    p.add_parameter("r", "rate", "A rate", FLOAT, false, "3.14");
    return true;
}

// Test parsing simple flag
bool test_parse_short_flag() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    std::vector<std::string> args = {"program", "-h"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    bool got_value = p.get_parameter_value_to("h", &help_value);
    ASSERT_TRUE(got_value);
    ASSERT_TRUE(help_value);
    
    return true;
}

bool test_parse_long_flag() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    std::vector<std::string> args = {"program", "--help"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    bool got_value = p.get_parameter_value_to("help", &help_value);
    ASSERT_TRUE(got_value);
    ASSERT_TRUE(help_value);
    
    return true;
}

// Test parsing string parameter
bool test_parse_string_parameter() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    std::vector<std::string> args = {"program", "-f", "test.txt"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    std::string file_value;
    bool got_value = p.get_parameter_value_to("f", &file_value);
    ASSERT_TRUE(got_value);
    ASSERT_STREQ("test.txt", file_value);
    
    return true;
}

bool test_parse_string_parameter_long() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    std::vector<std::string> args = {"program", "--file", "test.txt"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    std::string file_value;
    bool got_value = p.get_parameter_value_to("file", &file_value);
    ASSERT_TRUE(got_value);
    ASSERT_STREQ("test.txt", file_value);
    
    return true;
}

// Test parsing integer parameter
bool test_parse_integer_parameter() {
    parser p;
    p.add_parameter("n", "number", "A number", INTEGER, false, "0");
    
    std::vector<std::string> args = {"program", "-n", "123"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    i64 number_value;
    bool got_value = p.get_parameter_value_to("n", &number_value);
    ASSERT_TRUE(got_value);
    ASSERT_EQ(123, number_value);
    
    return true;
}

// Test parsing float parameter
bool test_parse_float_parameter() {
    parser p;
    p.add_parameter("r", "rate", "A rate", FLOAT, false, "0.0");
    
    std::vector<std::string> args = {"program", "-r", "3.14"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    f64 rate_value;
    bool got_value = p.get_parameter_value_to("r", &rate_value);
    ASSERT_TRUE(got_value);
    ASSERT_EQ(3.14, rate_value);
    
    return true;
}

// Test parsing multiple parameters
bool test_parse_multiple_parameters() {
    parser p;
    p.add_parameter("h", "help", "Show help", NONE, false);
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    p.add_parameter("n", "number", "A number", INTEGER, false, "0");
    
    std::vector<std::string> args = {"program", "-h", "-f", "test.txt", "-n", "42"};
    bool result = p.parse(args);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    ASSERT_TRUE(p.get_parameter_value_to("h", &help_value));
    ASSERT_TRUE(help_value);
    
    std::string file_value;
    ASSERT_TRUE(p.get_parameter_value_to("f", &file_value));
    ASSERT_STREQ("test.txt", file_value);
    
    i64 number_value;
    ASSERT_TRUE(p.get_parameter_value_to("n", &number_value));
    ASSERT_EQ(42, number_value);
    
    return true;
}

// Test parsing with argc/argv interface
bool test_parse_argc_argv() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    const char* argv[] = {"program", "-h"};
    int argc = 2;
    
    // Convert to char** for testing
    char* argv_copy[2];
    argv_copy[0] = const_cast<char*>(argv[0]);
    argv_copy[1] = const_cast<char*>(argv[1]);
    
    bool result = p.parse(argc, argv_copy);
    ASSERT_TRUE(result);
    
    bool help_value = false;
    bool got_value = p.get_parameter_value_to("h", &help_value);
    ASSERT_TRUE(got_value);
    ASSERT_TRUE(help_value);
    
    return true;
}

// Test error handling - unknown parameter
bool test_parse_unknown_parameter() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    std::vector<std::string> args = {"program", "-x"};
    bool result = p.parse(args);
    ASSERT_FALSE(result); // Should fail for unknown parameter
    
    return true;
}

// Test error handling - missing value
bool test_parse_missing_value() {
    parser p;
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    std::vector<std::string> args = {"program", "-f"};
    bool result = p.parse(args);
    ASSERT_FALSE(result); // Should fail for missing value
    
    return true;
}

// Test help message generation
bool test_help_message() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    p.add_parameter("f", "file", "Input file", STRING, false, "default.txt");
    
    // Parse something first to set program name
    std::vector<std::string> args = {"myprogram"};
    p.parse(args);
    
    std::string help_msg = p.get_help_message();
    ASSERT_TRUE(help_msg.find("Usage: myprogram [options]") != std::string::npos);
    ASSERT_TRUE(help_msg.find("-h, --help") != std::string::npos);
    ASSERT_TRUE(help_msg.find("Show help message") != std::string::npos);
    ASSERT_TRUE(help_msg.find("-f, --file") != std::string::npos);
    ASSERT_TRUE(help_msg.find("Input file") != std::string::npos);
    
    return true;
}

// Test getting non-existent parameter
bool test_get_nonexistent_parameter() {
    parser p;
    p.add_parameter("h", "help", "Show help message", NONE, false);
    
    bool dummy_value = false;
    bool got_value = p.get_parameter_value_to("nonexistent", &dummy_value);
    ASSERT_FALSE(got_value);
    
    return true;
}

// Main test runner
int main() {
    std::cout << "Running parser tests..." << std::endl;
    
    RUN_TEST(test_parser_construction);
    RUN_TEST(test_add_parameter_none);
    RUN_TEST(test_add_parameter_string);
    RUN_TEST(test_add_parameter_integer);
    RUN_TEST(test_add_parameter_float);
    RUN_TEST(test_parse_short_flag);
    RUN_TEST(test_parse_long_flag);
    RUN_TEST(test_parse_string_parameter);
    RUN_TEST(test_parse_string_parameter_long);
    RUN_TEST(test_parse_integer_parameter);
    RUN_TEST(test_parse_float_parameter);
    RUN_TEST(test_parse_multiple_parameters);
    RUN_TEST(test_parse_argc_argv);
    RUN_TEST(test_parse_unknown_parameter);
    RUN_TEST(test_parse_missing_value);
    RUN_TEST(test_help_message);
    RUN_TEST(test_get_nonexistent_parameter);
    
    print_test_summary();
    
    return tests_failed > 0 ? 1 : 0;
}