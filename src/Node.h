#ifndef NODE
#define NODE

namespace n
{
    template <typename T>
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

} // namespace n

#endif
