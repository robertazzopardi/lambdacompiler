#include "Tree.h"

namespace tree
{
    Tree::Tree()
    {
        root = new node::Node<token::Token>();
        curr = root;
    }

    Tree::~Tree()
    {
        delete root, curr;
        root = curr = nullptr;
    }

    void Tree::createLeft()
    {
        curr->leftNode = new node::Node<token::Token>();
    }

    void Tree::moveLeft()
    {
        node::Node<token::Token> *temp = curr;
        curr = curr->leftNode;
        curr->parentNode = temp;
    }

    void Tree::createRight()
    {
        curr->rightNode = new node::Node<token::Token>();
    }

    void Tree::moveRight()
    {
        node::Node<token::Token> *temp = curr;
        curr = curr->rightNode;
        curr->parentNode = temp;
    }

    template <class T>
    void Tree::setValue(T data)
    {
        curr->data = data;
    }
} // namespace tree