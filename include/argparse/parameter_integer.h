#ifndef ARGPARSE_PARAMETER_INTEGER_H
#define ARGPARSE_PARAMETER_INTEGER_H

#include "argparse/defs.h"
#include "argparse/parameter.h"

namespace argparse
{
    class parameter_integer : public parameter
    {
    public:
        parameter_integer(std::string short_name, std::string name, std::string description, int base = 10, bool is_signed = true);
        virtual ~parameter_integer();
        void set(std::string) override;
        void get_value_to(void*) override;
    private:
        i64 value;
        int base;
        bool is_signed;
    };
}

#endif
