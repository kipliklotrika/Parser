#ifndef PARSER_H
#define PARSER_H

#include "token.h"

class Lexer;
class AstNode;

/**
 * @brief The Parser class represents an implemetation of a simple calculator's expression parser
 *
 * The Parser class will for a given lexer produce a valid Abstract Syntax Tree (AST). It is one
 * time usage object and can be destroyed after usage. It implements the following grammar:
 *
 * <expression> := <term> {(PLUS|MINUS) <term>}
 * <term> := <factor> {(MULTIPLY|DIVIDE) <factor>}
 * <factor> := (NUMBER|LEFT_PARENTHESIS <expression> RIGHT_PARENTHESIS)
 *
 * and produce a AST tree in input has correct grammar.
 *
 * Usage:
 * const std::string input = " (2  + 3)  * 4  ";
 * std::stringstream stream(input);
 *
 * Lexer lexer(stream);
 * Parser parser(lexer);
 * Interpreter interpreter;
 *
 * try {
 *     auto node = parser.parse();
 * } catch(...) {
 *      ....
 * }
 *
 * double value = interpreter.interpret(*node);
 *
 * \see Interpreter
 * \see Lexer
 * \see AstNode
 */
class Parser
{
public:
    /**
     * @brief Parser Creates the parser object for a given Lexer.
     * @param lexer A valid Lexer object.
     */
    Parser(Lexer &lexer);

    /**
     * @brief parse Will parse everything that finds on input stream using given lexer.
     * @return A root node of a AST parsed from input stream or crash if syntax or grammar is
     *         incorrect.
     */
    const AstNode *parse();

private:
    /**
     * @brief expression Parse an expression from input stream.
     * @return A AST node of an expression if syntax and grammar is ok.
     */
    const AstNode *expression();

    /**
     * @brief term Parse a term from input stream.
     * @return A AST node of a term if syntax and grammar is ok.
     */
    const AstNode *term();

    /**
     * @brief factor Parse a factor from input stream.
     * @return A AST node of a factor if syntax and grammar is ok.
     */
    const AstNode *factor();

    /**
     * @brief eat 'Eats' a token if given token is the same as the read one and reads next. Crashes
     *        otherwise indicating the grammar is wrong.
     * @param type Expected token on the stream.
     */
    void eat(Token::TokenType type);

    Lexer &         _lexer;
    Token           _currentToken;
};

#endif // PARSER_H
