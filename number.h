#ifndef NUMBER_H
#define NUMBER_H

#include "astnode.h"
#include "token.h"

/**
 * @brief The Number class represents a digit (number) node in an AST
 *
 * The node must be construced with a valid digit value token otherwise will crash during
 * construction. \see Token.
 *
 * Usage:
 * Number numThree(Token(Token::TT_NUMBER, '3'));
 * int value = numTree.value() - '0';
 *
 */
class Number : public AstNode
{
public:
    /**
     * @brief Number Creates the Number object for a valid Token::TT_NUMBER token. Will crash
     *        otherwise.
     * @param token
     */
    Number(const Token &token);

    /**
     * @brief value Returns original token value.
     */
    char value() const { return _token.value(); }

    // AstNode interface
    AstNodeType type() const override { return AstNode::ANT_NUMBER; }

private:
    const Token     _token;
};

#endif // NUMBER_H
