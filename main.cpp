#include <iostream>
#include <sstream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "astnode.h"

/*
 * Example of an test function:
 *
double test(const std::string &string) {
    std::stringstream stream(string);
    Lexer lexer(stream);
    Parser parser(lexer);
    Interpreter interpreter;
    auto node = parser.parse();
    return interpreter.interpret(*node);
}
*/

int main()
{
    std::stringstream stream;
    std::string input;
    int length = 0;

    while (std::cin >> input) {
        stream << input;
        length += input.size();
    }

    if (length == 0) {
        std::cout
                << "Input empty. Provide input on the standard input like: echo \"2+2\" | Parser"
                << std::endl;
        return 0;
    }

    try {
        Lexer lexer(stream);
        Parser parser(lexer);
        Interpreter interpreter;

        auto node = parser.parse();

        std::cout << interpreter.interpret(*node) << std::endl;

        delete node;
    } catch (char const *reason) {
        std::cerr << reason << std::endl;
    } catch (...) {
        std::cerr << "Something realy wrong happened." << std::endl;
    }

    return 0;
}
