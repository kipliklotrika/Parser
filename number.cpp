#include "number.h"

Number::Number(const Token &token)
    : _token(token)
{
    if (this->_token.type() != Token::TT_NUMBER ||
        this->_token.value() < '0' || this->_token.value() > '9') {
        throw "Invalid number (digit) token";
    }
}
