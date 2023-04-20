#include "argparse/parameter_string.h"

using namespace argparse;

parameter_string::parameter_string(std::string short_name, std::string name, std::string description) : parameter(short_name, name, description, STRING)
{
    this->value = "";
}

parameter_string::~parameter_string()
{
}

void parameter_string::set(std::string value)
{
    this->value = value;
}

void parameter_string::get_value_to(void* p_value)
{
    *(std::string*)p_value = this->value;
}

