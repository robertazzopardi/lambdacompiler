#include <iostream>

#include "../include/Tree.hpp"

using namespace Tr;

Node::Node()
{
    left = right = parent = nullptr;
}

Tree::Tree()
{
    root = new Node();
    curr = root;
}

void Tree::createLeft()
{
    curr->left = new Node();
}

void Tree::moveLeft()
{
    Node *temp = curr;
    curr = curr->left;
    curr->parent = temp;
}

void Tree::cmsrLeft(std::string data)
{
    curr->left = new Node();

    Node *temp = curr;
    curr = curr->left;
    curr->parent = temp;

    curr->data = data;

    curr = curr->parent;
}

void Tree::cmsrRight(std::string data)
{
    curr->right = new Node();

    Node *temp = curr;
    curr = curr->right;
    curr->parent = temp;

    curr->data = data;

    curr = curr->parent;
}

void Tree::createRight()
{
    curr->right = new Node();
}

void Tree::moveRight()
{
    Node *temp = curr;
    curr = curr->right;
    curr->parent = temp;
}

void Tree::setValue(std::string data)
{
    curr->data = data;
}

void Tree::moveAbove()
{
    curr = curr->parent;
}

void Tree::printPreorder(class Node *node)
{
    if (node == nullptr)
        return;

    /* first print data of node */
    std::cout << node->data << " ";

    /* then recur on left sutree */
    printPreorder(node->left);

    /* now recur on right subtree */
    printPreorder(node->right);
}

void Tree::printPostorder(class Node *node)
{
    if (node == nullptr)
        return;

    // first recur on left subtree
    Tree::printPostorder(node->left);

    // then recur on right subtree
    Tree::printPostorder(node->right);

    // now deal with the node
    std::cout << node->data << " ";
}

/* Given a binary tree, print its nodes in inorder*/
void Tree::printInorder(class Node *node)
{
    if (node == nullptr)
        return;

    /* first recur on left child */
    printInorder(node->left);

    /* then print the data of node */
    std::cout << node->data << " ";

    /* now recur on right child */
    printInorder(node->right);
}