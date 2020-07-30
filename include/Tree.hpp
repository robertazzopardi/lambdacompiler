#ifndef TREE // include guard
#define TREE

#include <string>
#include <vector>

namespace Tr
{
    class Node
    {
    private:
    public:
        std::string data;
        Node *left, *right, *parent;
        Node();
        ~Node();
    };

    class Tree
    {
    private:
    public:
        Node *root, *curr;
        Tree();
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
    };
} // namespace Tr

#endif