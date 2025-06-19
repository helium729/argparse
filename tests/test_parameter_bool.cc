#include "argparse/parser.h"
#include <cassert>
#include <iostream>

using namespace argparse;

void test_bool_parameter() {
    parser p;
    p.add_bool("v", "verbose", "Enable verbose mode", false, false);
    const char* argv[] = {"prog", "--verbose", "true"};
    bool result = p.parse(3, const_cast<char**>(argv));
    assert(result);
    bool verbose = false;
    bool found = p.get_parameter_value_to("verbose", &verbose);
    assert(found);
    assert(verbose == true);

    // Test false value
    const char* argv2[] = {"prog", "--verbose", "false"};
    p.parse(3, const_cast<char**>(argv2));
    verbose = true;
    found = p.get_parameter_value_to("verbose", &verbose);
    assert(found);
    assert(verbose == false);

    // Test default value
    parser p2;
    p2.add_bool("d", "debug", "Enable debug", false, true);
    const char* argv3[] = {"prog"};
    p2.parse(1, const_cast<char**>(argv3));
    bool debug = false;
    found = p2.get_parameter_value_to("debug", &debug);
    assert(found);
    assert(debug == true);

    std::cout << "Bool parameter tests passed!\n";
}

int main() {
    test_bool_parameter();
    return 0;
}
