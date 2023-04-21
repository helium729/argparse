#include "argparse/parser.h"

int main(int argc, char** argv)
{
    argparse::parser parser;
    parser.add_parameter("h", "help", "Prints this help message", argparse::parameter_type::NONE);

    parser.parse(argc, argv);

    bool help = false;
    if (parser.get_parameter_value_to("h", &help))
    {
        std::cout << parser.get_help_message() << std::endl;
    }
    return 0;
}