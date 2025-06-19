#ifndef ARGPARSE_PARSER_H
#define ARGPARSE_PARSER_H

#include "argparse/defs.h"
#include "argparse/util.h"

namespace argparse
{
    
    class parser
    {
    public:
        parser();
        virtual ~parser();

        void add_parameter(std::string short_name, std::string name, std::string description, parameter_type type=NONE, bool required=false, std::string default_value=std::string(""));
        void add_bool(std::string short_name, std::string name, std::string description, bool required = false, bool default_value = false);

        std::string get_help_message();

        bool parse(std::vector<std::string> args);
        bool parse(int argc, char** argv);

        bool get_parameter_value_to(std::string flag, void* value_buf);

        // Auto-help configuration
        void set_auto_help(bool enable);

    private:
        std::map<std::string, parameter*> parameters;
        std::string program_name;

        std::map<std::string, std::string> short_name_query;
        std::map<std::string, std::string> name_query;

        bool auto_help_enabled;

        // Helper methods for auto-help
        bool is_help_requested();
        void print_help_and_exit();

    };
}

#endif