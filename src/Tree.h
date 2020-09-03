#ifndef _TREE_H_ // include guard
#define _TREE_H_

#include <vector>
#include <iostream>
#include <cmath>

#include "Lexer.h"
#include "Node.h"

namespace tree
{
    class Tree
    {
    private:
    public:
        node::Node<lexer::Token> *root, *curr;
        Tree();
        ~Tree();
        // returns the depth of a node in the tree
        int getDepth(const node::Node<lexer::Token> *node);

        // creates a new left node of the current node
        void createLeft();

        // traverses to the left node of the current node
        void moveLeft();

        // creates a new right node of the current node
        void createRight();

        // traverses to the right node of the current node
        void moveRight();

        // sets the value of the current node to the passed parameter
        template <class T>
        void setValue(T data);

        // prints the tree with a pre-order traversal
        // template <class T>
        void printPreorder(const node::Node<lexer::Token> *node);

        // prints the tree with a post-order traversal
        // template <class T>
        void printPostorder(const node::Node<lexer::Token> *node);

        // prints the tree with a in-order traversal
        // template <class T>
        void printInorder(const node::Node<lexer::Token> *node);

        // recursively traverse the tree
        // template <class T>
        void formatPrintTree(const node::Node<lexer::Token> *p, int level, int depth);

        // prints the abstract syntax tree with formatting
        void printTreeHelper(Tree *tree);
    };

    template <class T>
    void Tree::setValue(T data)
    {
        curr->data = data;
    }

} // namespace tree

#endif