#include "argparse/parameter_none.h"

using namespace argparse;

parameter_none::parameter_none(std::string short_name, std::string name, std::string description) : parameter(short_name, name, description, NONE)
{
    this->is_set = false;
}

parameter_none::~parameter_none()
{
}

void parameter_none::set(std::string value)
{
    this->is_set = true;
}

void parameter_none::get_value_to(void* p_value)
{
    *(bool*)p_value = this->is_set;
}