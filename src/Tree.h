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

        template <class T>
        void deleteTree(node::Node<T> *node)
        {
            if (node == nullptr)
                return;

            /* first delete both subtrees */
            deleteTree(node->leftNode);
            deleteTree(node->rightNode);

            /* then delete the node */
            // cout << "\n Deleting node: " << node->data;
            delete node;
        }

        // sets the value of the current node to the passed parameter
        template <class T>
        void setValue(T data);

        // prints the tree with a pre-order traversal
        void printPreorder(const node::Node<lexer::Token> *node);

        // prints the tree with a post-order traversal
        void printPostorder(const node::Node<lexer::Token> *node);

        // prints the tree with a in-order traversal
        void printInorder(const node::Node<lexer::Token> *node);

        void pPrint(const node::Node<lexer::Token> *node);
        void pPrintHelper(const node::Node<lexer::Token> *ndoe);

        // recursively traverse the tree
        void formatPrintTree(const node::Node<lexer::Token> *p, int level, int depth);

        // prints the abstract syntax tree with formatting
        void printTreeHelper(Tree *tree);

        void setTreeNodeParents(node::Node<lexer::Token> *node);

        int toInt(std::string str);

        // template <typename T>
        // int max_depth(node::Node<T> *n)
        // {
        //     if (!n)
        //         return 0;
        //     return 1 + std::max(max_depth(n->leftNode), max_depth(n->rightNode));
        // }

        // template <typename T>
        // void prt(node::Node<T> *n)
        // {
        //     struct node_depth
        //     {
        //         node::Node<T> *n;
        //         int lvl;
        //         node_depth(node::Node<T> *n_, int lvl_) : n(n_), lvl(lvl_) {}
        //     };

        //     int depth = max_depth(n);

        //     char buf[1024];
        //     int last_lvl = 0;
        //     int offset = (1 << depth) - 1;

        //     // using a queue means we perform a breadth first iteration through the tree
        //     std ::list<node_depth> q;

        //     q.push_back(node_depth(n, last_lvl));

        //     while (q.size())
        //     {
        //         const node_depth &nd = *q.begin();

        //         // moving to a new level in the tree, output a new line and calculate new offset
        //         if (last_lvl != nd.lvl)
        //         {
        //             std::cout << "\n";

        //             last_lvl = nd.lvl;
        //             offset = (1 << (depth - nd.lvl)) - 1;
        //         }

        //         // output <offset><data><offset>
        //         if (nd.n)
        //         {
        //             if (nd.n->data.attribute == lexer::Attribute::integer || nd.n->data.attribute == lexer::Attribute::floatpt)
        //             {
        //                 sprintf(buf, " %*s%d%*s", offset, " ", std::atoi(nd.n->data.value.c_str()), offset, " ");
        //             }
        //             else
        //             {
        //                 sprintf(buf, " %*s%s%*s", offset, " ", nd.n->data.value.c_str(), offset, " ");
        //             }
        //         }
        //         else
        //         {
        //             sprintf(buf, " %*s", offset << 1, " ");
        //         }
        //         std::cout << buf;

        //         if (nd.n)
        //         {
        //             q.push_back(node_depth(nd.n->leftNode, last_lvl + 1));
        //             q.push_back(node_depth(nd.n->rightNode, last_lvl + 1));
        //         }

        //         q.pop_front();
        //     }
        //     std::cout << "\n";
        // }
    };

    // template <class T>
    // void Tree::setValue(T data)
    // {
    //     curr->data = data;
    // }
} // namespace tree

#endif