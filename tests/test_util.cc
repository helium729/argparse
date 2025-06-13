#include "test_framework.h"
#include "argparse/util.h"
#include "argparse/parameter.h"
#include "argparse/parameter_none.h"
#include "argparse/parameter_integer.h"
#include "argparse/parameter_string.h"
#include "argparse/parameter_float.h"

using namespace argparse;

bool test_util_create_parameter_none() {
    parameter* p = util::create_parameter("h", "help", "Show help", NONE);
    ASSERT_TRUE(p != nullptr);
    ASSERT_EQ(NONE, p->get_type());
    ASSERT_STREQ("h", p->get_short_name());
    ASSERT_STREQ("help", p->get_name());
    ASSERT_STREQ("Show help", p->get_description());
    
    delete p;
    return true;
}

bool test_util_create_parameter_integer() {
    parameter* p = util::create_parameter("n", "number", "A number", INTEGER);
    ASSERT_TRUE(p != nullptr);
    ASSERT_EQ(INTEGER, p->get_type());
    ASSERT_STREQ("n", p->get_short_name());
    ASSERT_STREQ("number", p->get_name());
    ASSERT_STREQ("A number", p->get_description());
    
    delete p;
    return true;
}

bool test_util_create_parameter_string() {
    parameter* p = util::create_parameter("s", "string", "A string", STRING);
    ASSERT_TRUE(p != nullptr);
    ASSERT_EQ(STRING, p->get_type());
    ASSERT_STREQ("s", p->get_short_name());
    ASSERT_STREQ("string", p->get_name());
    ASSERT_STREQ("A string", p->get_description());
    
    delete p;
    return true;
}

bool test_util_create_parameter_float() {
    parameter* p = util::create_parameter("f", "float", "A float", FLOAT);
    ASSERT_TRUE(p != nullptr);
    ASSERT_EQ(FLOAT, p->get_type());
    ASSERT_STREQ("f", p->get_short_name());
    ASSERT_STREQ("float", p->get_name());
    ASSERT_STREQ("A float", p->get_description());
    
    delete p;
    return true;
}

bool test_util_create_parameter_default() {
    parameter* p = util::create_parameter("d", "default", "Default type");
    ASSERT_TRUE(p != nullptr);
    ASSERT_EQ(NONE, p->get_type()); // Default should be NONE
    ASSERT_STREQ("d", p->get_short_name());
    ASSERT_STREQ("default", p->get_name());
    ASSERT_STREQ("Default type", p->get_description());
    
    delete p;
    return true;
}

bool test_util_create_parameter_empty_names() {
    // Test with empty short name
    parameter* p1 = util::create_parameter("", "long", "Long only", NONE);
    ASSERT_TRUE(p1 != nullptr);
    ASSERT_STREQ("", p1->get_short_name());
    ASSERT_STREQ("long", p1->get_name());
    delete p1;
    
    // Test with empty long name
    parameter* p2 = util::create_parameter("s", "", "Short only", NONE);
    ASSERT_TRUE(p2 != nullptr);
    ASSERT_STREQ("s", p2->get_short_name());
    ASSERT_STREQ("", p2->get_name());
    delete p2;
    
    return true;
}

bool test_util_parameter_functionality() {
    // Test that created parameters actually work
    parameter* p_none = util::create_parameter("h", "help", "Help", NONE);
    ASSERT_TRUE(p_none != nullptr);
    
    // Test setting and getting for NONE type
    p_none->set("");
    bool help_value = false;
    p_none->get_value_to(&help_value);
    ASSERT_TRUE(help_value);
    delete p_none;
    
    // Test setting and getting for INTEGER type
    parameter* p_int = util::create_parameter("n", "number", "Number", INTEGER);
    ASSERT_TRUE(p_int != nullptr);
    p_int->set("42");
    i64 int_value;
    p_int->get_value_to(&int_value);
    ASSERT_EQ(42, int_value);
    delete p_int;
    
    // Test setting and getting for STRING type
    parameter* p_str = util::create_parameter("s", "string", "String", STRING);
    ASSERT_TRUE(p_str != nullptr);
    p_str->set("hello");
    std::string str_value;
    p_str->get_value_to(&str_value);
    ASSERT_STREQ("hello", str_value);
    delete p_str;
    
    // Test setting and getting for FLOAT type
    parameter* p_float = util::create_parameter("f", "float", "Float", FLOAT);
    ASSERT_TRUE(p_float != nullptr);
    p_float->set("3.14");
    f64 float_value;
    p_float->get_value_to(&float_value);
    ASSERT_EQ(3.14, float_value);
    delete p_float;
    
    return true;
}

bool test_util_parameter_required() {
    parameter* p = util::create_parameter("r", "required", "Required param", STRING);
    ASSERT_TRUE(p != nullptr);
    
    // Test required functionality
    ASSERT_FALSE(p->get_required()); // Default not required
    p->set_required(true);
    ASSERT_TRUE(p->get_required());
    p->set_required(false);
    ASSERT_FALSE(p->get_required());
    
    delete p;
    return true;
}

// Main test runner
int main() {
    std::cout << "Running util tests..." << std::endl;
    
    RUN_TEST(test_util_create_parameter_none);
    RUN_TEST(test_util_create_parameter_integer);
    RUN_TEST(test_util_create_parameter_string);
    RUN_TEST(test_util_create_parameter_float);
    RUN_TEST(test_util_create_parameter_default);
    RUN_TEST(test_util_create_parameter_empty_names);
    RUN_TEST(test_util_parameter_functionality);
    RUN_TEST(test_util_parameter_required);
    
    print_test_summary();
    
    return tests_failed > 0 ? 1 : 0;
}