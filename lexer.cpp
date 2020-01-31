#include "lexer.h"

#include "token.h"

Lexer::Lexer(std::stringstream &stringStream)
    : _stringStream(stringStream)
{

}

Token Lexer::getNextToken()
{
    char tokenChar;

    if (!(_stringStream >> tokenChar)) {
        return Token(Token::TT_EOF, '\0');
    }

    // We only expect one-character tokens such as digits, parentheses and operators.
    // Operatror >> will skip all whitespaces and give next valid token.

    switch (tokenChar) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return Token(Token::TT_NUMBER, tokenChar);
        case '+':
            return Token(Token::TT_PLUS, tokenChar);
        case '-':
            return Token(Token::TT_MINUS, tokenChar);
        case '*':
            return Token(Token::TT_MULTIPLY, tokenChar);
        case '/':
            return Token(Token::TT_DIVIDE, tokenChar);
        case '(':
            return Token(Token::TT_LEFT_PARENTHESIS, tokenChar);
        case ')':
            return Token(Token::TT_RIGHT_PARENTHESIS, tokenChar);

        default:
        throw "Invalid character."; // TODO: add more details.
    }

}
