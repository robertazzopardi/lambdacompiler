<<<<<<< HEAD
#ifndef _TREE_H_ // include guard
#define _TREE_H_
=======
#ifndef TREE // include guard
#define TREE
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f

#include <vector>
#include <iostream>
#include <cmath>

<<<<<<< HEAD
#include "Lexer.h"
#include "Node.h"

namespace tree
=======
#include "Constants.h"
#include "Node.h"

using namespace n;

namespace tr
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
{
    class Tree
    {
    private:
    public:
<<<<<<< HEAD
        Tree();
        ~Tree();

        // store the value of the root node of the tree and the current node
        // in a traversal
        node::Node<lexer::Token> *root, *curr;

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
        void printPreorder(const node::Node<lexer::Token> *node);

        // prints the tree with a post-order traversal
        void printPostorder(const node::Node<lexer::Token> *node);

        // prints the tree with a in-order traversal
        void printInorder(const node::Node<lexer::Token> *node);

        // recursively traverse the tree
        void formatPrintTree(const node::Node<lexer::Token> *p, int level, int depth);

        // prints the abstract syntax tree with formatting
        void printTreeHelper(Tree *tree);
=======
        n::Node<std::string> *root, *curr;
        Tree();
        ~Tree();
        // returns the depth of a node in the tree
        template <class T>
        int getDepth(const n::Node<T> *node)
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
        // creates a new left node of the current node
        void createLeft();
        // traverses to the left node of the current node
        void moveLeft();
        // creates a new right node of the current node
        void createRight();
        // traverses to the right node of the current node
        void moveRight();
        // sets the value of the current node to the passed parameter
        void setValue(std::string data);

        // prints the tree with a pre-order traversal
        template <class T>
        void printPreorder(const n::Node<T> *node)
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

        // prints the tree with a post-order traversal
        template <class T>
        void printPostorder(const n::Node<T> *node)
        {
            if (node == nullptr)
                return;

            // first recur on left subtree
            Tree::printPostorder(node->leftNode);

            // then recur on right subtree
            Tree::printPostorder(node->rightNode);

            // now deal with the node
            std::cout << node->data << " ";
        }

        // prints the tree with a in-order traversal
        template <class T>
        void printInorder(const n::Node<T> *node)
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

        /* Given a binary tree, print its nodes in inorder*/
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
    };

    template <class T>
    void Tree::setValue(T data)
    {
        curr->data = data;
    }
} // namespace tree

#endif