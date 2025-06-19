#ifndef ARGPARSE_PARAMETER_BOOL_H
#define ARGPARSE_PARAMETER_BOOL_H

#include "argparse/parameter.h"
#include <string>

namespace argparse {
    class parameter_bool : public parameter {
    public:
        parameter_bool(std::string short_name, std::string name, std::string description);
        void set(std::string value) override;
        void get_value_to(void* p_value) override;
    private:
        bool value;
    };
}

#endif // ARGPARSE_PARAMETER_BOOL_H
