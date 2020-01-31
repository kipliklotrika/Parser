#ifndef INTERPRETER_H
#define INTERPRETER_H

class AstNode;

///
/// \brief The Interpreter class represent a post-order interpreter object for a given AST.
///
/// This class represent one post-order interpreter for a given AST. For more \see AstNode.
///
/// Usage:
/// Interpreter i;
/// double result = i.iterpret(rootNode);
class Interpreter
{
public:
    Interpreter() {};

    /**
     * @brief interpret Will interpret the value of an AST by giving the root of the tree.
     * @param node The tree root node.
     * @return Value for a given AST tree.
     */
    double interpret(const AstNode &node);

private:
    /**
     * @brief visit Visitor pattern implementation for a given tree node. Goes in post-order
     *      traversal.
     * @param node AST node.
     * @return Value for the whole subtree.
     */
    double visit(const AstNode &node);
};

#endif // INTERPRETER_H
