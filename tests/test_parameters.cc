#include "test_framework.h"
#include "argparse/parameter_none.h"
#include "argparse/parameter_integer.h"
#include "argparse/parameter_string.h"
#include "argparse/parameter_float.h"
#include <string>

using namespace argparse;

// Test parameter_none
bool test_parameter_none_construction() {
    parameter_none p("h", "help", "Show help");
    ASSERT_STREQ("h", p.get_short_name());
    ASSERT_STREQ("help", p.get_name());
    ASSERT_STREQ("Show help", p.get_description());
    ASSERT_EQ(NONE, p.get_type());
    return true;
}

bool test_parameter_none_set_get() {
    parameter_none p("h", "help", "Show help");
    
    // Initially not set
    bool value = true;
    p.get_value_to(&value);
    ASSERT_FALSE(value);
    
    // After setting
    p.set("");
    p.get_value_to(&value);
    ASSERT_TRUE(value);
    
    return true;
}

bool test_parameter_none_required() {
    parameter_none p("h", "help", "Show help");
    
    ASSERT_FALSE(p.get_required()); // Default not required
    
    p.set_required(true);
    ASSERT_TRUE(p.get_required());
    
    p.set_required(false);
    ASSERT_FALSE(p.get_required());
    
    return true;
}

// Test parameter_integer
bool test_parameter_integer_construction() {
    parameter_integer p("n", "number", "A number");
    ASSERT_STREQ("n", p.get_short_name());
    ASSERT_STREQ("number", p.get_name());
    ASSERT_STREQ("A number", p.get_description());
    ASSERT_EQ(INTEGER, p.get_type());
    return true;
}

bool test_parameter_integer_set_get() {
    parameter_integer p("n", "number", "A number");
    
    // Set and get positive integer
    p.set("123");
    i64 value;
    p.get_value_to(&value);
    ASSERT_EQ(123, value);
    
    // Set and get negative integer
    p.set("-456");
    p.get_value_to(&value);
    ASSERT_EQ(-456, value);
    
    return true;
}

bool test_parameter_integer_different_bases() {
    // Test hex base
    parameter_integer p_hex("x", "hex", "Hex number", 16);
    p_hex.set("ff");
    i64 value_hex;
    p_hex.get_value_to(&value_hex);
    ASSERT_EQ(255, value_hex);
    
    // Test octal base
    parameter_integer p_oct("o", "octal", "Octal number", 8);
    p_oct.set("10");
    i64 value_oct;
    p_oct.get_value_to(&value_oct);
    ASSERT_EQ(8, value_oct);
    
    return true;
}

bool test_parameter_integer_unsigned() {
    parameter_integer p("u", "unsigned", "Unsigned number", 10, false);
    p.set("123");
    i64 value;
    p.get_value_to(&value);
    ASSERT_EQ(123, value);
    
    return true;
}

// Test parameter_string
bool test_parameter_string_construction() {
    parameter_string p("s", "string", "A string");
    ASSERT_STREQ("s", p.get_short_name());
    ASSERT_STREQ("string", p.get_name());
    ASSERT_STREQ("A string", p.get_description());
    ASSERT_EQ(STRING, p.get_type());
    return true;
}

bool test_parameter_string_set_get() {
    parameter_string p("s", "string", "A string");
    
    // Initially empty
    std::string value;
    p.get_value_to(&value);
    ASSERT_STREQ("", value);
    
    // Set and get string
    p.set("hello world");
    p.get_value_to(&value);
    ASSERT_STREQ("hello world", value);
    
    // Set empty string
    p.set("");
    p.get_value_to(&value);
    ASSERT_STREQ("", value);
    
    return true;
}

// Test parameter_float
bool test_parameter_float_construction() {
    parameter_float p("f", "float", "A float");
    ASSERT_STREQ("f", p.get_short_name());
    ASSERT_STREQ("float", p.get_name());
    ASSERT_STREQ("A float", p.get_description());
    ASSERT_EQ(FLOAT, p.get_type());
    return true;
}

bool test_parameter_float_set_get() {
    parameter_float p("f", "float", "A float");
    
    // Initially zero
    f64 value;
    p.get_value_to(&value);
    ASSERT_EQ(0.0, value);
    
    // Set and get positive float
    p.set("3.14");
    p.get_value_to(&value);
    ASSERT_EQ(3.14, value);
    
    // Set and get negative float
    p.set("-2.5");
    p.get_value_to(&value);
    ASSERT_EQ(-2.5, value);
    
    // Set integer as float
    p.set("42");
    p.get_value_to(&value);
    ASSERT_EQ(42.0, value);
    
    return true;
}

// Test parameter names with empty values
bool test_parameter_empty_names() {
    // Parameter with only short name
    parameter_none p1("h", "", "Help");
    ASSERT_STREQ("h", p1.get_short_name());
    ASSERT_STREQ("", p1.get_name());
    
    // Parameter with only long name
    parameter_none p2("", "help", "Help");
    ASSERT_STREQ("", p2.get_short_name());
    ASSERT_STREQ("help", p2.get_name());
    
    return true;
}

// Main test runner
int main() {
    std::cout << "Running parameter tests..." << std::endl;
    
    RUN_TEST(test_parameter_none_construction);
    RUN_TEST(test_parameter_none_set_get);
    RUN_TEST(test_parameter_none_required);
    RUN_TEST(test_parameter_integer_construction);
    RUN_TEST(test_parameter_integer_set_get);
    RUN_TEST(test_parameter_integer_different_bases);
    RUN_TEST(test_parameter_integer_unsigned);
    RUN_TEST(test_parameter_string_construction);
    RUN_TEST(test_parameter_string_set_get);
    RUN_TEST(test_parameter_float_construction);
    RUN_TEST(test_parameter_float_set_get);
    RUN_TEST(test_parameter_empty_names);
    
    print_test_summary();
    
    return tests_failed > 0 ? 1 : 0;
}