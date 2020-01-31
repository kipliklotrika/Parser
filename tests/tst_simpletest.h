#ifndef TST_SIMPLETEST_H
#define TST_SIMPLETEST_H

#include <sstream>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <astnode.h>
#include <number.h>
#include <binaryoperator.h>
#include <lexer.h>
#include <parser.h>
#include <interpreter.h>

using namespace testing;

TEST(ParserTests, simpletest)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(ParserTests, NumberConstruction)
{
    Number *number;
    Token validToken(Token::TT_NUMBER, '0');

    // Number is valid only for characters between '0' and '9'
    for (int i = 0; i < 10; ++i) {
        number = new Number(Token(Token::TT_NUMBER, '0' + i));
        ASSERT_EQ(number->value(), '0' + i);
        ASSERT_EQ(number->type(), AstNode::ANT_NUMBER);
        delete number;
    }

    // Check for invalid Numbers
    ASSERT_ANY_THROW(new Number(Token(Token::TT_NUMBER, '0' - 1)));
    ASSERT_ANY_THROW(new Number(Token(Token::TT_NUMBER, '9' + 1)));

    for (int i = Token::TT_PLUS; i <= Token::TT_EOF; ++i) {
        ASSERT_ANY_THROW(new Number(Token(static_cast<Token::TokenType>(i), '0')));
    }
}

TEST(ParserTest, BinaryOperatorConstruction)
{
    BinaryOperator *bOperator;
    auto genNum = [](int num) {
        return new Number(Token(Token::TT_NUMBER, '0' + num));
    };

    // Binary operator should be valid for any binary operator token.
    Token::TokenType validOperators[] =
        { Token::TT_PLUS, Token::TT_MINUS, Token::TT_MULTIPLY, Token::TT_DIVIDE };
    char operatorChars[] = { '+', '-', '*', '/' };

    for (unsigned int i = 0; i < sizeof(validOperators) / sizeof(validOperators[0]); ++i) {
        const Number *n1 = genNum(1);
        const Number *n2 = genNum(2);
        bOperator = new BinaryOperator(n1,
                                       Token(validOperators[i], operatorChars[i]),
                                       n2);

        ASSERT_EQ(n1, &bOperator->left());
        ASSERT_EQ(n2, &bOperator->right());
        ASSERT_EQ(validOperators[i], bOperator->op());
        ASSERT_EQ(AstNode::ANT_BINARY_OPERATOR, bOperator->type());

        delete bOperator;
    }

    // Check for invalid operators.
    ASSERT_ANY_THROW(new BinaryOperator(genNum(1), Token(Token::TT_NUMBER, '0'), genNum(2)));
    ASSERT_ANY_THROW(new BinaryOperator(genNum(1), Token(Token::TT_NUMBER, '0'), genNum(1)));
    ASSERT_ANY_THROW(new BinaryOperator(genNum(1), Token(Token::TT_LEFT_PARENTHESIS, '('), genNum(2)));
    ASSERT_ANY_THROW(new BinaryOperator(genNum(1), Token(Token::TT_RIGHT_PARENTHESIS, ')'), genNum(2)));
}

TEST(ParserTest, Lexer)
{
    Lexer *lexer;

    // Simple behavior.
    std::stringstream stream(std::string("1+1"));
    lexer = new Lexer(stream);

    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '1'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_PLUS, '+'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '1'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));

    delete lexer;

    // White spaces should be ignored
    stream = std::stringstream(std::string("   1 + 1  "));
    lexer = new Lexer(stream);

    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '1'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_PLUS, '+'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '1'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));

    delete lexer;

    // Allowed chars
    stream = std::stringstream(std::string("0123456789()+-*/"));
    lexer = new Lexer(stream);

    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '0'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '1'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '2'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '3'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '4'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '5'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '6'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '7'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '8'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '9'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_LEFT_PARENTHESIS, '('));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_RIGHT_PARENTHESIS, ')'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_PLUS, '+'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_MINUS, '-'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_MULTIPLY, '*'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_DIVIDE, '/'));
    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));

    delete lexer;

    // Invalid char
    stream = std::stringstream(std::string("2 % 3"));
    lexer = new Lexer(stream);

    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_NUMBER, '2'));
    ASSERT_ANY_THROW(lexer->getNextToken());

    delete lexer;

    // Empty input
    stream = std::stringstream(std::string(""));
    lexer = new Lexer(stream);

    ASSERT_EQ(lexer->getNextToken(), Token(Token::TT_EOF, '\0'));

    delete lexer;
}

TEST(ParserTest, ParserAst)
{
    Lexer *lexer;
    Parser *parser;

    {
        // Simple behavior with valid gramatics.
        //   +
        // 1   1
        std::stringstream stream(std::string("1+1"));
        lexer = new Lexer(stream);
        parser = new Parser(*lexer);

        const AstNode *rootNode = parser->parse();
        ASSERT_EQ(rootNode->type(), AstNode::ANT_BINARY_OPERATOR);
        const BinaryOperator *bOperatorNode = static_cast<const BinaryOperator *>(rootNode);
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode->left()).value(), '1');
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode->right()).value(), '1');

        delete rootNode;
        delete parser;
        delete lexer;
    }
    {
        // Simple behavior with valid gramatics.
        //   +
        // 1   +
        //   2   3
        std::stringstream stream(std::string("1+(2*3)"));
        lexer = new Lexer(stream);
        parser = new Parser(*lexer);

        const AstNode *rootNode = parser->parse();
        ASSERT_EQ(rootNode->type(), AstNode::ANT_BINARY_OPERATOR);
        const BinaryOperator *bOperatorNode = static_cast<const BinaryOperator *>(rootNode);
        ASSERT_EQ(bOperatorNode->op(), Token::TT_PLUS);
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode->left()).value(), '1');
        ASSERT_EQ(bOperatorNode->right().type(), AstNode::ANT_BINARY_OPERATOR);

        const BinaryOperator *bOperatorNode2 =
                static_cast<const BinaryOperator *>(&bOperatorNode->right());
        ASSERT_EQ(bOperatorNode2->op(), Token::TT_MULTIPLY);
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode2->left()).value(), '2');
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode2->right()).value(), '3');


        delete rootNode;
        delete parser;
        delete lexer;
    }

    {
        // Simple behavior with valid gramatics.
        //      *
        //   +     3
        // 1   2
        std::stringstream stream(std::string("(1+2)*3"));
        lexer = new Lexer(stream);
        parser = new Parser(*lexer);

        const AstNode *rootNode = parser->parse();
        ASSERT_EQ(rootNode->type(), AstNode::ANT_BINARY_OPERATOR);
        const BinaryOperator *bOperatorNode = static_cast<const BinaryOperator *>(rootNode);
        ASSERT_EQ(bOperatorNode->op(), Token::TT_MULTIPLY);
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode->right()).value(), '3');
        ASSERT_EQ(bOperatorNode->left().type(), AstNode::ANT_BINARY_OPERATOR);

        const BinaryOperator *bOperatorNode2 =
                static_cast<const BinaryOperator *>(&bOperatorNode->left());
        ASSERT_EQ(bOperatorNode2->op(), Token::TT_PLUS);
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode2->left()).value(), '1');
        ASSERT_EQ(static_cast<const Number &>(bOperatorNode2->right()).value(), '2');


        delete rootNode;
        delete parser;
        delete lexer;
    }
}

TEST(ParserTest, Interpreter)
{
    auto calculate = [](const std::string &string) {
            Lexer *lexer;
            Parser *parser;
            Interpreter interpreter;

            std::stringstream stream(string);
            lexer = new Lexer(stream);
            parser = new Parser(*lexer);

            const AstNode *rootNode = parser->parse();
            double result = interpreter.interpret(*rootNode);

            delete rootNode;
            delete parser;
            delete lexer;

            return result;
    };

    // Simple behavior cases with valid syntax & gramatic.
    ASSERT_EQ(calculate("1+1"), 2.);
    ASSERT_EQ(calculate("0+1+2+3+4+5+6+7+8+9"), 45.);
    ASSERT_EQ(calculate("(1)"), 1.);
    ASSERT_EQ(calculate("1+2*3"), 7.);
    ASSERT_EQ(calculate("1+(2*3)"), 7.);
    ASSERT_EQ(calculate("(1+2)*3"), 9.);
    ASSERT_EQ(calculate("((1+1)*(1+1+1))*3"), 18.);
    ASSERT_EQ(calculate("   ( (1  + 1)   * ( 1  + 1 +1) )*3   "), 18.);
    ASSERT_EQ(calculate("5/2"), 2.5);
    ASSERT_EQ(calculate("1-1"), 0.);
    ASSERT_EQ(calculate("1-9"), -8.);
    ASSERT_EQ(calculate("5/0"), std::numeric_limits<double>::infinity());
    ASSERT_EQ(calculate("(2+2+(3-1)+4) * 9"), 90.);

    // Invalid syntax or gramatic.
    ASSERT_ANY_THROW(calculate("10+1"));
    ASSERT_ANY_THROW(calculate("-1"));
    ASSERT_ANY_THROW(calculate(" ( "));
    ASSERT_ANY_THROW(calculate("((1)"));
    ASSERT_ANY_THROW(calculate("1+aaa"));
    ASSERT_ANY_THROW(calculate("+"));
    ASSERT_ANY_THROW(calculate("1+2% 5"));
    ASSERT_ANY_THROW(calculate("1+()"));
    ASSERT_ANY_THROW(calculate("()    + 1 "));
    ASSERT_ANY_THROW(calculate("1+1   )   "));
    ASSERT_ANY_THROW(calculate("1-1   )   "));
    ASSERT_ANY_THROW(calculate("1*1   )   "));
    ASSERT_ANY_THROW(calculate("1/1   )   "));
}

#endif // TST_SIMPLETEST_H
