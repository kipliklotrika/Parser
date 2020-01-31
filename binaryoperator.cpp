#include "binaryoperator.h"


BinaryOperator::BinaryOperator(const AstNode *left, const Token &op, const AstNode *right)
    : _left(left), _right(right), _operator(op)
{
    if (left == nullptr || right == nullptr) {
        throw "Invalid params.";
    }
    if (&left == &right) {
        throw "Left and right are the same.";
    }

    switch(_operator.type()) {
        case Token::TT_PLUS:
        case Token::TT_MINUS:
        case Token::TT_MULTIPLY:
        case Token::TT_DIVIDE:
            // Allowed operators.
        break;
        default:
            throw "Invalid operator.";
    }
}

BinaryOperator::~BinaryOperator()
{
    delete _left;
    delete _right;
    _left = _right = nullptr;
}
