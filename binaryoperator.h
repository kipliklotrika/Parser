#ifndef BINARYOPERATOR_H
#define BINARYOPERATOR_H

#include "astnode.h"
#include "token.h"

/**
 * @brief The BinaryOperator class represents a binary operator node in AST.
 *
 * The BinaryOperator must have its left and right AstNode and the operator which represent the
 * operation performed between them.
 * The BinaryOperator will take ownership of the 'left' and 'right' object and delete them on
 * destruction
 *
 * Usage:
 * BinaryOperator(leftNode, Token(Token::TT_PLUS, '+'), rightNode);
 */
class BinaryOperator : public AstNode
{
public:
    /**
     * @brief BinaryOperator Creates BinaryOperator object.
     * @param left The left node in an AST tree.
     * @param op The binary operator. Can only be Token::TT_PLUS,...,Token::TT_DIVIDE
     *  otherwise will crash.
     * @param right The right node in an AST tree.
     */
    BinaryOperator(const AstNode *left, const Token &op, const AstNode *right);
    ~BinaryOperator();

    // Getters.
    const AstNode &left() const { return *_left; }
    const AstNode &right() const { return *_right; }
    Token::TokenType op() const { return _operator.type(); }

    // AstNode interface
    /**
     * @return Returns AstNode::ANT_BINARY_OPERATOR.
     */
    AstNodeType type() const override { return AstNode::ANT_BINARY_OPERATOR; }

private:
    const AstNode *         _left;
    const AstNode *         _right;
    const Token             _operator;
};

#endif // BINARYOPERATOR_H
