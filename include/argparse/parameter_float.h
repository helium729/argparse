#ifndef ARGPARSE_PARAMETER_FLOAT_H
#define ARGPARSE_PARAMETER_FLOAT_H

#include "argparse/defs.h"
#include "argparse/parameter.h"

namespace argparse
{
    class parameter_float : public parameter
    {
    public:
        parameter_float(std::string short_name, std::string name, std::string description);
        virtual ~parameter_float();
        void set(std::string) override;
        void get_value_to(void*) override;
    private:
        f64 value;
    };
}

#endif