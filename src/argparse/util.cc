#include "argparse/util.h"
#include "argparse/parameter_bool.h"

using namespace argparse;

parameter* util::create_parameter(std::string short_name, std::string name, std::string description, parameter_type type)
{
    switch (type)
    {
    case parameter_type::NONE:
        return new parameter_none(short_name, name, description);
    case parameter_type::INTEGER:
        return new parameter_integer(short_name, name, description);
    case parameter_type::STRING:
        return new parameter_string(short_name, name, description);
    case parameter_type::FLOAT:
        return new parameter_float(short_name, name, description);
    case parameter_type::BOOL:
        return new parameter_bool(short_name, name, description);
    default:
        std::cerr << "Unknown parameter type: " << type << std::endl;
        return nullptr;
    }
}