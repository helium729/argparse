#ifndef ARGPARSE_UTIL_H
#define ARGPARSE_UTIL_H

#include "argparse/defs.h"

//parameter includes
#include "argparse/parameter.h"
#include "argparse/parameter_none.h"
#include "argparse/parameter_integer.h"
#include "argparse/parameter_string.h"
#include "argparse/parameter_float.h"

namespace argparse
{
    class util
    {
    public:
        static parameter* create_parameter(std::string short_name, std::string name, std::string description, parameter_type type=parameter_type::NONE);
    };
}

#endif