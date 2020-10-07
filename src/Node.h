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
            this->leftNode = nullptr;
            this->rightNode = nullptr;
            this->parentNode = nullptr;
        };

        Node(T value)
        {
            this->data = value;
            this->leftNode = nullptr;
            this->rightNode = nullptr;
            this->parentNode = nullptr;
        };

        Node(T func, Node *right)
        {
            this->data = func;
            this->rightNode = right;
            this->leftNode = nullptr;
            this->parentNode = nullptr;
        }

        Node(T op, Node *left, Node *right)
        {
            this->data = op;
            this->leftNode = left;
            this->rightNode = right;
            this->parentNode = nullptr;
        };

        ~Node()
        {
            delete leftNode;
            delete rightNode;
            delete parentNode;
            leftNode = nullptr;
            rightNode = nullptr;
            parentNode = nullptr;
        };
    };
} // namespace node

#endif
