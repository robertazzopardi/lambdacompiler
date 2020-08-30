#include "Tree.h"

tr::Tree::Tree()
{
    root = new n::Node<std::string>();
    curr = root;
}

tr::Tree::~Tree()
{
    delete root, curr;
    root = curr = nullptr;
}

void tr::Tree::createLeft()
{
    curr->leftNode = new n::Node<std::string>();
}

void tr::Tree::moveLeft()
{
    n::Node<std::string> *temp = curr;
    curr = curr->leftNode;
    curr->parentNode = temp;
}

void tr::Tree::createRight()
{
    curr->rightNode = new n::Node<std::string>();
}

void tr::Tree::moveRight()
{
    n::Node<std::string> *temp = curr;
    curr = curr->rightNode;
    curr->parentNode = temp;
}

void tr::Tree::setValue(std::string data)
{
    curr->data = data;
}
