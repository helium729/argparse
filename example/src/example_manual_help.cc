#include "argparse/parser.h"
#include <iostream>

int main(int argc, char** argv)
{
    argparse::parser parser;
    
    // Disable auto-help for manual control (backward compatibility)
    parser.set_auto_help(false);
    
    // Add parameters
    parser.add_parameter("h", "help", "Show this help message", argparse::parameter_type::NONE);
    parser.add_parameter("f", "file", "Input file path", argparse::parameter_type::STRING, false, "input.txt");
    parser.add_parameter("v", "verbose", "Enable verbose output", argparse::parameter_type::NONE);
    
    // Parse arguments
    bool parse_success = parser.parse(argc, argv);
    
    if (!parse_success) {
        std::cerr << "Failed to parse arguments!" << std::endl;
        std::cout << parser.get_help_message() << std::endl;
        return 1;
    }
    
    // Check if help was requested
    bool help = false;
    if (parser.get_parameter_value_to("h", &help) && help) {
        std::cout << parser.get_help_message() << std::endl;
        return 0;
    }
    
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
    
    return 0;
}