#ifndef _TREE_H_ // include guard
#define _TREE_H_

#include <vector>
#include <iostream>
#include <cmath>
#include <list>

#include "Stack.h"
#include "Lexer.h"
#include "Node.h"

namespace tree
{
    class Tree
    {
    private:
    public:
        Tree();
        ~Tree();

        // store the value of the root node of the tree and the current node
        // in a traversal
        node::Node<lexer::Token> *root, *curr;

        // prints the tree with a post-order traversal
        void printPostorder(const node::Node<lexer::Token> *node);

        void setTreeNodeParents(node::Node<lexer::Token> *node);
    };

} // namespace tree

#endif