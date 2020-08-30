#ifndef TREE // include guard
#define TREE

#include <vector>
#include <iostream>

#include "Constants.h"
#include "Node.h"

using namespace n;

namespace tr
{
    class Tree
    {
    private:
    public:
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
    };
} // namespace tr

#endif