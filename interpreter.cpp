#include "interpreter.h"

#include "astnode.h"
#include "number.h"
#include "binaryoperator.h"

double Interpreter::interpret(const AstNode &node)
{
    return this->visit(node);
}

double Interpreter::visit(const AstNode &node)
{
    switch (node.type()) {
    case AstNode::ANT_NUMBER:
        return static_cast<const Number &>(node).value() - '0';
    case AstNode::ANT_BINARY_OPERATOR:
    {
        const BinaryOperator &op = static_cast<const BinaryOperator &>(node);
        switch (op.op()) {
        case Token::TT_PLUS:
            return this->visit(op.left()) + this->visit(op.right());
        case Token::TT_MINUS:
            return this->visit(op.left()) - this->visit(op.right());
        case Token::TT_MULTIPLY:
            return this->visit(op.left()) * this->visit(op.right());
        case Token::TT_DIVIDE:
            return this->visit(op.left()) / this->visit(op.right());
        default:
            throw "Something went wrong. Unimplemented operator.";
        }
    }
    default:
        throw "Something went wrong. Unimplemented node.";
    }
}
