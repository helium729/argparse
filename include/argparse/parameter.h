#ifndef ARGPARSE_PARAMETER_H 
#define ARGPARSE_PARAMETER_H

#include "argparse/defs.h"

namespace argparse
{
    enum parameter_type
    {
        NONE, INTEGER, STRING, FLOAT, BOOL
    };

    class parameter
    {
    public:
        parameter(std::string short_name, std::string name, std::string description, parameter_type type);
        virtual ~parameter();

        std::string get_short_name();
        std::string get_name();
        std::string get_description();
        
        virtual void set(std::string);
        virtual void get_value_to(void*);

        void set_required(bool);
        bool get_required();

        parameter_type get_type();

    private:
        std::string short_name;
        std::string name;
        std::string description;
        parameter_type type;
        
        bool required;
    };



}

#endif