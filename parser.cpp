#include "parser.h"

#include "lexer.h"
#include "number.h"
#include "binaryoperator.h"

Parser::Parser(Lexer &lexer)
    : _lexer(lexer), _currentToken(lexer.getNextToken())
{

}

const AstNode *Parser::parse()
{
    auto rootNode = this->expression();
    // Check if there is unconsumed token, if so than it's a syntax error.
    if (this->_currentToken.type() != Token::TT_EOF) {
        throw "Invalid syntax";
    }

    return rootNode;
}

const AstNode *Parser::expression()
{
    // From grammar:
    // <expression> := <term> {(PLUS|MINUS) <term>}

    auto node = this->term();

    while (this->_currentToken.type() == Token::TT_PLUS ||
           this->_currentToken.type() == Token::TT_MINUS) {

        const Token token = this->_currentToken;
        this->eat(this->_currentToken.type());  // Eat '+' or '-' token.

        node = new BinaryOperator(node, token, this->term());
    }

    return node;
}

const AstNode *Parser::term()
{
    // From grammar:
    // <term> := <factor> {(MULTIPLY|DIVIDE) <factor>}

    auto node = this->factor();

    while (this->_currentToken.type() == Token::TT_MULTIPLY ||
           this->_currentToken.type() == Token::TT_DIVIDE) {

        const Token token = this->_currentToken;
        this->eat(this->_currentToken.type());  // Eat '*' or '/' token.

        node = new BinaryOperator(node, token, this->factor());
    }

    return node;
}

const AstNode *Parser::factor()
{
    // From grammar:
    // <factor> := (NUMBER|LEFT_PARENTHESIS <expression> RIGHT_PARENTHESIS)

    if (this->_currentToken.type() == Token::TT_NUMBER) {
        const Token token = this->_currentToken;
        this->eat(Token::TT_NUMBER);

        if (this->_currentToken.type() == Token::TT_NUMBER) {
            // We found multidigit number in input.
            throw "Invalid syntax";
        }

        return new Number(token);
    } else if (this->_currentToken.type() == Token::TT_LEFT_PARENTHESIS) {
        this->eat(Token::TT_LEFT_PARENTHESIS);
        auto node = this->expression();
        this->eat(Token::TT_RIGHT_PARENTHESIS);
        return node;
    } else {
        throw "Something went wrong!"; // Unexpected situation. API misuse.
    }
}

void Parser::eat(Token::TokenType type)
{
    if (_currentToken.type() == type) {
        this->_currentToken = this->_lexer.getNextToken();
    } else {
        throw "Invalid syntax."; // TODO: Add more details about the error.
    }
}
