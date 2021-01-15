#include "Tree.h"

namespace tree
{
    Tree::Tree()
    {
        this->root = new node::Node<lexer::Token>();
        this->curr = root;
    }

    Tree::~Tree()
    {
        delete root;
        delete curr;
        root = nullptr;
        curr = nullptr;
    }

    void Tree::printPostorder(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        // first recur on left subtree
        printPostorder(node->leftNode);

        // then recur on right subtree
        printPostorder(node->rightNode);

        // now deal with the node
        std::cout << node->data.value << " ";
    }

    void Tree::setTreeNodeParents(node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        if (node->leftNode != nullptr)
            node->leftNode->parentNode = node;
        if (node->rightNode != nullptr)
            node->rightNode->parentNode = node;

        setTreeNodeParents(node->leftNode);
        setTreeNodeParents(node->rightNode);
    }
} // namespace tree
