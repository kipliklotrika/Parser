#ifndef LEXER_H
#define LEXER_H

#include <sstream>
#include <string>

class Token;

/**
 * @brief The Lexer class represent a basic lexer wrapper for a calculator syntax \see Parser
 *
 * The Lexer object wraps tokenization parsing and will return a next token for every character the
 * Lexer reads from an input stream. Whitespaces are ignored. Each token represent one character
 * since there are no multicharacter tokens \see Token.
 *
 * Usage:
 * Lexer lexer(inputStream);
 * Token token;
 * while ((token = lexer.getNextToken).type() != Token::TT_EOF) {
 *  ...
 * }
 *
 */
class Lexer
{
public:
    /**
     * @brief Lexer Creates the Lexer object with given input stream.
     * @param stringStream Input string stream.
     */
    Lexer(std::stringstream &stringStream);

    /**
     * @brief getNextToken Returns next token from an input stream. Token will be EOF if end of
     *        stream is reached.
     */
    Token getNextToken();

private:
    Lexer(const Lexer &);

    std::stringstream &   _stringStream;
};

#endif // LEXER_H
