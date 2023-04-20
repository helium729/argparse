#include "argparse/parameter_integer.h"

using namespace argparse;

parameter_integer::parameter_integer(std::string short_name, std::string name, std::string description, int base, bool is_signed) : parameter(short_name, name, description, INTEGER)
{
    this->base = base;
    this->value = 0;
    this->is_signed = is_signed;
}

parameter_integer::~parameter_integer()
{
}

void parameter_integer::set(std::string value)
{
    if (this->is_signed)
    {
        this->value = std::stoll(value, nullptr, this->base);
    }
    else
    {
        this->value = std::stoull(value, nullptr, this->base);
    }
}

void parameter_integer::get_value_to(void* p_value)
{
    *(i64*)p_value = this->value;
}
