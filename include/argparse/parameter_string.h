#ifndef ARGPARSE_PARAMETER_STRING_H
#define ARGPARSE_PARAMETER_STRING_H

#include "argparse/defs.h"
#include "argparse/parameter.h"

namespace argparse
{
    class parameter_string : public parameter
    {
    public:
        parameter_string(std::string short_name, std::string name, std::string description);
        virtual ~parameter_string();
        void set(std::string) override;
        void get_value_to(void*) override;
    private:
        std::string value;
    };
}

#endif