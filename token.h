#ifndef TOKEN_H
#define TOKEN_H

/**
 * @brief The Token class represent wraper around token concept for the calculator syntax
 *
 * Token class object represent what one lexer has read from an input. In its essence it is a pair
 * of interpreted value and actual value read from input. In a case of the calculatro syntax valid
 * tokens can be one of the following characters 0123456789+*-/() and EOF character.
 * \see Lexer
 */
class Token
{
public:
    enum TokenType {
        TT_NUMBER,
        TT_PLUS,
        TT_MINUS,
        TT_MULTIPLY,
        TT_DIVIDE,
        TT_LEFT_PARENTHESIS,
        TT_RIGHT_PARENTHESIS,
        TT_EOF,
    };

    Token(TokenType type, char value)
        : _type(type), _value(value) {}

    TokenType type() const { return _type; }
    char value() const { return _value; }

private:
    Token();

    TokenType   _type;
    char        _value;
};

inline bool operator==(const Token &left, const Token& right) {
    return left.type() == right.type() && left.value() == right.value();
};

#endif // TOKEN_H
