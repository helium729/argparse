#ifndef ARGPARSE_PARAMETER_NONE_H
#define ARGPARSE_PARAMETER_NONE_H

#include "argparse/defs.h"
#include "argparse/parameter.h"

namespace argparse
{
    class parameter_none : public parameter
    {
    public:
        parameter_none(std::string short_name, std::string name, std::string description);
        virtual ~parameter_none();
        void set(std::string) override;
        void get_value_to(void*) override;

    private:
        bool is_set;
    };
}

#endif