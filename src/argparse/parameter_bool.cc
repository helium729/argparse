#include "argparse/parameter_bool.h"
#include <algorithm>

using namespace argparse;

parameter_bool::parameter_bool(std::string short_name, std::string name, std::string description)
    : parameter(short_name, name, description, BOOL), value(false) {}

void parameter_bool::set(std::string value_str) {
    std::string lower = value_str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "1" || lower == "true" || lower == "yes" || lower == "on") {
        value = true;
    } else {
        value = false;
    }
}

void parameter_bool::get_value_to(void* p_value) {
    if (p_value) {
        *static_cast<bool*>(p_value) = value;
    }
}
