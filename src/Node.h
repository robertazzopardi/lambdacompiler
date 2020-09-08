<<<<<<< HEAD
#ifndef _NODE_H_
#define _NODE_H_

namespace node
{
    template <class T>
=======
#ifndef NODE
#define NODE

namespace n
{
    template <typename T>
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
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
<<<<<<< HEAD

=======
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
        Node(T value)
        {
            this->data = value;
            this->leftNode = this->rightNode = nullptr;
        };
<<<<<<< HEAD

=======
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
        Node(T op, Node *left, Node *right)
        {
            this->data = op;
            this->leftNode = left;
            this->rightNode = right;
        };
<<<<<<< HEAD

=======
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
        ~Node()
        {
            delete leftNode, rightNode, parentNode;
            leftNode = rightNode = parentNode = nullptr;
        };
    };
<<<<<<< HEAD
} // namespace node
=======

} // namespace n
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f

#endif
