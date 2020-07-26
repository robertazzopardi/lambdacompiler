#ifndef TREE // include guard
#define TREE

#include <string>
#include <vector>

namespace Tr
{
    class Node
    {
    private:
        /* data */
    public:
        std::string data;
        Tr::Node *left, *right, *parent;
        Node();
        ~Node();
        void setData(std::string data);
    };

    Node::Node()
    {
        left = right = parent = NULL;
    }

    void Node::setData(std::string data)
    {
        this->data = data;
    }

    Node::~Node()
    {
    }

    void printPreorder(struct Node *node)
    {
        if (node == NULL)
            return;

        /* first print data of node */
        std::cout << node->data << " ";

        /* then recur on left sutree */
        printPreorder(node->left);

        /* now recur on right subtree */
        printPreorder(node->right);
    }

    // struct Node
    // {
    //     int data;
    //     struct Node *left, *right;
    //     Node(int data)
    //     {
    //         this->data = data;
    //         left = right = NULL;
    //     }

    //     ~Node()
    //     {
    //         delete &left;
    //         delete &right;
    //     }
    // };

    // // Node Class
    // class Node
    // {
    // private:
    // public:
    //     std::string value;
    //     Node();
    // };

    // Node::Node()
    // {
    // }

    // Tree Template
    template <typename T>
    class Tree
    {
    private:
    public:
        // Node leftNode;
        // Node currentNode;
        // Node rightNode;
        // Node root;
        std::vector<Node> stack;
        Tree();
    };

    template <typename T>
    Tree<T>::Tree()
    {
        // stack.push_back();
    }

} // namespace Tr

#endif