#include <iostream>

#include "../include/Tree.hpp"
#include "../include/Parser.hpp"

tr::Node::Node()
{
    left = right = parent = nullptr;
}

tr::Node::Node(std::string number)
{
    this->data = number;
    this->left = this->right = nullptr;
}

tr::Node::Node(std::string op, Node *left, Node *right)
{
    this->data = op;
    this->left = left;
    this->right = right;
}

tr::Node::~Node()
{
    delete left, right, parent;
    left = right = parent = nullptr;
}

tr::Tree::Tree()
{
    root = new Node();
    curr = root;
}

tr::Tree::~Tree()
{
    delete root, curr;
    root = curr = nullptr;
}

void tr::Tree::createLeft()
{
    curr->left = new Node();
}

void tr::Tree::moveLeft()
{
    Node *temp = curr;
    curr = curr->left;
    curr->parent = temp;
}

void tr::Tree::cmsrLeft(std::string data)
{
    curr->left = new Node();

    Node *temp = curr;
    curr = curr->left;
    curr->parent = temp;

    curr->data = data;

    curr = curr->parent;
}

void tr::Tree::cmsrRight(std::string data)
{
    curr->right = new Node();

    Node *temp = curr;
    curr = curr->right;
    curr->parent = temp;

    curr->data = data;

    curr = curr->parent;
}

void tr::Tree::createRight()
{
    curr->right = new Node();
}

void tr::Tree::moveRight()
{
    Node *temp = curr;
    curr = curr->right;
    curr->parent = temp;
}

void tr::Tree::setValue(std::string data)
{
    curr->data = data;
}

void tr::Tree::moveAbove()
{
    curr = curr->parent;
}

void tr::Tree::printPreorder(class Node *node)
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

void tr::Tree::printPostorder(class Node *node)
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
void tr::Tree::printInorder(class Node *node)
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

void tr::Tree::setNumbers(class Node *node, std::string val)
{
    if (node == nullptr)
    {
        return;
    }

    // if (!node->data.empty())
    //     std::cout << node->data;

    // // first recur on left subtree
    // setNumbers(node->left, val);

    // // then recur on right subtree
    // setNumbers(node->right, val);

    if (node->left != nullptr && node->right != nullptr)
    {
        std::cout << node->data;
        // return;
        if (node->left->data.empty() && node->right->data.empty())
        {
            node->left->data = val;
            node->right->data = val;
        }
        else if (node->left->data.empty() && !node->right->data.empty())
        {
            node->left->data = val;
        }
        else if (!node->left->data.empty() && node->right->data.empty())
        {
            node->right->data = val;
        }
        else
        {
        }
    }

    // first recur on left subtree
    setNumbers(node->left, val);

    // then recur on right subtree
    setNumbers(node->right, val);
}

tr::Node *tr::Tree::rightRotation(class Node *y)
{
    class tr::Node *x = y->left, *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return new root
    return x;
}

void tr::Tree::leftRotation(class Node *node)
{
}

tr::Node *tr::Tree::createExpressionTree(std::vector<std::string> prefixExpression)
{
    auto element = prefixExpression[0];
    prefixExpression.erase(prefixExpression.begin());

    if (p::Parser::isInteger(element))
    {

        class tr::Node *newRoot = new tr::Node();
        newRoot->data = element;

        return newRoot;
    }
    else
    {
        class tr::Node *left = new tr::Node();
        class tr::Node *right = new tr::Node();
        class tr::Node *newRoot = new tr::Node();
        left = tr::Tree::createExpressionTree(prefixExpression);
        right = tr::Tree::createExpressionTree(prefixExpression);
        newRoot->left = left;
        newRoot->right = right;
        newRoot->data = element;
        return newRoot;
    }
}
