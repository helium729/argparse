#include "argparse/parameter_float.h"

using namespace argparse;

parameter_float::parameter_float(std::string short_name, std::string name, std::string description) : parameter(short_name, name, description, FLOAT)
{
    this->value = 0.0;
}

parameter_float::~parameter_float()
{
}

void parameter_float::set(std::string value)
{
    this->value = std::stod(value);
}

void parameter_float::get_value_to(void* p_value)
{
    *(f64*)p_value = this->value;
}