#ifndef TREE // include guard
#define TREE

#include "Constants.h"

#include <vector>
// #include <string>
#include <iostream>

namespace tr
{
    class Node
    {
    private:
    public:
        std::string data;
        Node *left, *right, *parent;
        Node();
        Node(std::string number);
        Node(std::string op, Node *left, Node *right);
        ~Node();
    };

    class Tree
    {
    private:
    public:
        Node *root, *curr;
        Tree();
        ~Tree();
        int getDepth(tr::Node *node);
        void createLeft();
        void moveLeft();
        void createRight();
        void moveRight();
        void cmsrLeft(std::string data);
        void cmsrRight(std::string data);
        void setValue(std::string data);
        void moveAbove();
        void printPreorder(class Node *node);
        void printPostorder(class Node *node);
        void printInorder(class Node *node);
        void setNumbers(class Node *node, std::string val);
        tr::Node *rightRotation(class Node *node);
        void leftRotation(class Node *node);
        tr::Node *createExpressionTree(std::vector<std::string> prefixExpression);
    };
} // namespace tr

#endif