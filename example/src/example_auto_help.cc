#include "argparse/parser.h"
#include <iostream>

int main(int argc, char** argv)
{
    argparse::parser parser;
    
    // Add parameters
    parser.add_parameter("h", "help", "Show this help message", argparse::parameter_type::NONE);
    parser.add_parameter("f", "file", "Input file path", argparse::parameter_type::STRING, false, "input.txt");
    parser.add_parameter("v", "verbose", "Enable verbose output", argparse::parameter_type::NONE);
    parser.add_parameter("n", "number", "A number parameter", argparse::parameter_type::INTEGER, false, "42");
    
    // Parse arguments
    // Note: With auto-help enabled (default), help will be automatically printed and program will exit
    // when -h/--help is used or when parsing fails (unknown parameters, missing values, etc.)
    bool parse_success = parser.parse(argc, argv);
    
    if (parse_success) {
        std::cout << "Arguments parsed successfully!" << std::endl;
        
        // Get parameter values
        std::string file_value;
        if (parser.get_parameter_value_to("file", &file_value)) {
            std::cout << "File: " << file_value << std::endl;
        }
        
        bool verbose_value = false;
        if (parser.get_parameter_value_to("verbose", &verbose_value) && verbose_value) {
            std::cout << "Verbose mode enabled" << std::endl;
        }
        
        int number_value;
        if (parser.get_parameter_value_to("number", &number_value)) {
            std::cout << "Number: " << number_value << std::endl;
        }
    } else {
        // This should not be reached when auto-help is enabled (default)
        // because parse errors will automatically print help and exit
        std::cout << "Parse failed!" << std::endl;
        return 1;
    }
    
    return 0;
}