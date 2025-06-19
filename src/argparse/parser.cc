#include "argparse/parser.h"
#include <iostream>
#include <cstdlib>

using namespace argparse;

parser::parser()
{
    auto_help_enabled = true; // Enable auto-help by default
}

parser::~parser()
{
    // Delete all parameters
    for (auto p_parameter : this->parameters)
    {
        delete p_parameter.second;
    }
}

void argparse::parser::add_parameter(std::string short_name, std::string name, std::string description, parameter_type type, bool required, std::string default_value)
{
    parameter* p_parameter = nullptr;
    p_parameter = util::create_parameter(short_name, name, description, type);
    if (p_parameter != nullptr)
    {
        if (type != NONE)
            p_parameter->set(default_value);
        p_parameter->set_required(required);
        std::string key = short_name + '\n' + name;
        parameters[key] = p_parameter;
        if (short_name != "")
        {
            short_name_query[short_name] = key;
        }
        if (name != "")
        {
            name_query[name] = key;
        }
    }
}

void parser::add_bool(std::string short_name, std::string name, std::string description, bool required, bool default_value) {
    parameter* p_parameter = util::create_parameter(short_name, name, description, parameter_type::BOOL);
    if (p_parameter != nullptr) {
        p_parameter->set(default_value ? "true" : "false");
        p_parameter->set_required(required);
        std::string key = short_name + '\n' + name;
        parameters[key] = p_parameter;
        if (short_name != "") {
            short_name_query[short_name] = key;
        }
        if (name != "") {
            name_query[name] = key;
        }
    }
}

std::string argparse::parser::get_help_message()
{
    std::string help_message = "";
    help_message += std::string("Usage: ") + program_name + " [options]";
    for (auto p_parameter : this->parameters)
    {
        help_message += std::string("\n");
        if (p_parameter.second->get_short_name() != "")
        {
            help_message += std::string("-") + p_parameter.second->get_short_name();
            help_message += std::string(", ");
        }
        if (p_parameter.second->get_name() != "")
        {
            help_message += std::string("--") + p_parameter.second->get_name();
        }
        help_message += std::string("\t") + p_parameter.second->get_description();
        if (p_parameter.second->get_short_name() == "" && p_parameter.second->get_name() == "")
        {
            help_message = "error: parameter has no name or short name";
            return help_message;
        }
    }
    return help_message;
}

bool parser::parse(std::vector<std::string> args)
{
    //get program name by removing path
    this->program_name = args[0];
    size_t last_slash = this->program_name.find_last_of("\\/");
    if (last_slash != std::string::npos)
    {
        this->program_name = this->program_name.substr(last_slash + 1);
    }

    args.erase(args.begin());

    for (u64 i = 0; i < args.size(); i++)
    {
        std::string current = args[i];
        std::string key = "";
        if (current[0] == '-')
        {
            bool short_name = true;
            current = current.substr(1);
            if (current[0] == '-')
            {
                short_name = false;
                current = current.substr(1);
            }
            if (short_name)
            {
                key = short_name_query[current];
            }
            else
            {
                key = name_query[current];
            }
            if (key == "")
            {
                std::cerr << "error: unknown parameter " << current << std::endl;
                if (auto_help_enabled)
                {
                    print_help_and_exit();
                }
                return false;
            }
            parameter* p_parameter = parameters[key];
            if (p_parameter->get_type() == NONE)
            {
                p_parameter->set("");
            }
            else
            {
                i++;
                if (i >= args.size() || args[i][0] == '-')
                {
                    std::cerr << "error: parameter " << current << " requires a value" << std::endl;
                    if (auto_help_enabled)
                    {
                        print_help_and_exit();
                    }
                    return false;
                }
                p_parameter->set(args[i]);
            }
        }
        else 
        {
            if (auto_help_enabled)
            {
                print_help_and_exit();
            }
            return false;
        }
    }
    
    // Check if help was requested after successful parsing
    if (auto_help_enabled && is_help_requested())
    {
        print_help_and_exit();
    }
    
    return true;
}

bool parser::parse(int argc, char** argv)
{
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
    return parse(args);
}

bool parser::get_parameter_value_to(std::string flag, void* value_buf)
{
    std::string key = "";
    
    // Handle flags with dashes
    if (flag[0] == '-')
    {
        flag = flag.substr(1);
        if (flag[0] == '-')
        {
            // Long name (--flag)
            flag = flag.substr(1);
            key = name_query[flag];
        }
        else
        {
            // Short name (-f)
            key = short_name_query[flag];
        }
    }
    else
    {
        // No dashes - try short name first, then long name
        key = short_name_query[flag];
        if (key == "")
        {
            key = name_query[flag];
        }
    }
    
    parameter* p_parameter = parameters[key];
    if (p_parameter == nullptr)
    {
        return false;
    }
    p_parameter->get_value_to(value_buf);
    return true;
}

void parser::set_auto_help(bool enable)
{
    auto_help_enabled = enable;
}

bool parser::is_help_requested()
{
    // Check if help parameter exists and is set
    bool help_value = false;
    if (get_parameter_value_to("h", &help_value) && help_value)
    {
        return true;
    }
    if (get_parameter_value_to("help", &help_value) && help_value)
    {
        return true;
    }
    return false;
}

void parser::print_help_and_exit()
{
    std::cout << get_help_message() << std::endl;
    exit(0);
}