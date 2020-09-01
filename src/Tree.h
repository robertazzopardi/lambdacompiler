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
        template <class T>
        int getDepth(const node::Node<T> *node);

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
        template <class T>
        void printPreorder(const node::Node<T> *node);

        // prints the tree with a post-order traversal
        template <class T>
        void printPostorder(const node::Node<T> *node);

        // prints the tree with a in-order traversal
        template <class T>
        void printInorder(const node::Node<T> *node);

        // recursively traverse the tree
        template <class T>
        void formatPrintTree(const node::Node<T> *p, int level, int depth);

        // prints the abstract syntax tree with formatting
        void printTreeHelper(Tree *tree);
    };

    template <class T>
    void Tree::setValue(T data)
    {
        curr->data = data;
    }

    template <class T>
    int Tree::getDepth(const node::Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
        {
            /* compute the height of each subtree */
            int lheight = getDepth(node->leftNode);
            int rheight = getDepth(node->rightNode);

            /* use the larger one */
            if (lheight > rheight)
                return (lheight + 1);
            else
                return (rheight + 1);
        }
    }

    template <class T>
    void Tree::printPreorder(const node::Node<T> *node)
    {
        if (node == nullptr)
            return;

        /* first print data of node */
        std::cout << node->data << " ";

        /* then recur on left sutree */
        printPreorder(node->leftNode);

        /* now recur on right subtree */
        printPreorder(node->rightNode);
    }

    template <class T>
    void Tree::printPostorder(const node::Node<T> *node)
    {
        if (node == nullptr)
            return;

        // first recur on left subtree
        printPostorder(node->leftNode);

        // then recur on right subtree
        printPostorder(node->rightNode);

        // now deal with the node
        std::cout << node->data << " ";
    }

    template <class T>
    void Tree::printInorder(const node::Node<T> *node)
    {
        if (node == nullptr)
            return;

        /* first recur on left child */
        printInorder(node->leftNode);

        /* then print the data of node */
        std::cout << node->data << " ";

        /* now recur on right child */
        printInorder(node->rightNode);
    }

    template <class T>
    void Tree::formatPrintTree(const node::Node<T> *node, int level, int depth)
    {
        if (node == nullptr)
            return;

        if (level == 1)
        {
            std::cout << node->data;
        }
        else if (level > 1)
        {
            formatPrintTree(node->leftNode, level - 1, depth);

            for (size_t j = 0; j < std::pow(2, depth - level - 1); j++)
                std::cout << " ";

            formatPrintTree(node->rightNode, level - 1, depth);
        }
    }
} // namespace tree

#endif