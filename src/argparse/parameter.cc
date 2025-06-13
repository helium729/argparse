#include "argparse/parameter.h"

using namespace argparse;

parameter::parameter(std::string short_name, std::string name, std::string description, parameter_type type)
{
    this->short_name = short_name;
    this->name = name;
    this->description = description;
    this->type = type;
    this->required = false; // Initialize required field
}

parameter::~parameter()
{
}

std::string parameter::get_short_name()
{
    return this->short_name;
}

std::string parameter::get_name()
{
    return this->name;
}

std::string parameter::get_description()
{
    return this->description;
}

void parameter::set(std::string value)
{
}

void parameter::get_value_to(void* p_value)
{
}

void parameter::set_required(bool required)
{
    this->required = required;
}

bool parameter::get_required()
{
    return this->required;
}

parameter_type parameter::get_type()
{
    return this->type;
}