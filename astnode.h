#ifndef ASTNODE_H
#define ASTNODE_H

/**
 * @brief The AstNode class represents a base object in the AST
 *
 * The AstNode should be used to represent one node in a Abstract Syntax Tree (AST). This class
 * should be used to represent an AST tree for grammar defined in \see Parser class. There are
 * two possible nodes: binary operator (+,-,* and /) and a digit (number) \see BinaryOperator and
 * \see Number.
 */
class AstNode
{
public:
    enum AstNodeType {
        ANT_BINARY_OPERATOR,
        ANT_NUMBER
    };

    AstNode();
    virtual ~AstNode() = 0;

    /**
     * @brief type returns type of the AST node.
     */
    virtual AstNodeType type() const = 0;

};

#endif // ASTNODE_H
