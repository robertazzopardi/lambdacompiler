#ifndef _NODE_H_
#define _NODE_H_

namespace node
{
    template <class T>
    class Node
    {
    private:
    public:
        T data;
        Node *leftNode, *rightNode, *parentNode;

        Node()
        {
            leftNode = rightNode = parentNode = nullptr;
        };

        Node(T value)
        {
            this->data = value;
            this->leftNode = this->rightNode = nullptr;
        };

        // Node(T func, Node *left)
        // {
        //     this->data = func;
        //     this->leftNode = left;
        // }
        Node(T func, Node *right)
        {
            this->data = func;
            this->rightNode = right;
        }

        Node(T op, Node *left, Node *right)
        {
            this->data = op;
            this->leftNode = left;
            this->rightNode = right;
        };

        ~Node()
        {
            delete leftNode, rightNode, parentNode;
            leftNode = rightNode = parentNode = nullptr;
        };
    };
} // namespace node

#endif
