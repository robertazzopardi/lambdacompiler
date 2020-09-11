#include "Tree.h"

namespace tree
{
    Tree::Tree()
    {
        root = new node::Node<lexer::Token>();
        curr = root;
    }

    Tree::~Tree()
    {
        delete root, curr;
        root = curr = nullptr;
    }

    void Tree::createLeft()
    {
        curr->leftNode = new node::Node<lexer::Token>();
    }

    void Tree::moveLeft()
    {
        node::Node<lexer::Token> *temp = curr;
        curr = curr->leftNode;
        curr->parentNode = temp;
    }

    void Tree::createRight()
    {
        curr->rightNode = new node::Node<lexer::Token>();
    }

    void Tree::moveRight()
    {
        node::Node<lexer::Token> *temp = curr;
        curr = curr->rightNode;
        curr->parentNode = temp;
    }

    void Tree::printTreeHelper(tree::Tree *tree)
    {
        int h = tree->getDepth(tree->curr);
        for (size_t i = 1; i <= h; i++)
        {
            if (i > 1)
            {
                std::cout << std::endl;
                for (size_t j = 0; j < std::pow(2, h - i) - 1; j++)
                    std::cout << "  ";
            }
            else
            {
                for (size_t j = 0; j < std::pow(2, h - i) - 1; j++)
                    std::cout << " ";
            }

            formatPrintTree(tree->curr, i, h);
        }
        std::cout << "\n"
                  << std::endl;
    }

    int Tree::getDepth(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return 0;
        else
        {
            // compute the height of each subtree
            int lheight = getDepth(node->leftNode);
            int rheight = getDepth(node->rightNode);

            // use the larger one
            if (lheight > rheight)
                return (lheight + 1);
            else
                return (rheight + 1);
        }
    }

    void Tree::printPreorder(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        /* first print data of node */
        std::cout << node->data << " ";

        /* then recur on left sutree */
        printPreorder(node->leftNode);

        /* now recur on right subtree */
        printPreorder(node->rightNode);
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
        std::cout << node->data << " ";
    }

    void Tree::printInorder(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        /* first recur on left child */
        printInorder(node->leftNode);

        /* then print the data of node */
        std::cout << node->data << " ";

        /* now recur on right child */
        printInorder(node->rightNode);
    }

    void Tree::formatPrintTree(const node::Node<lexer::Token> *node, int level, int depth)
    {
        if (node == nullptr)
            return;

        if (level == 1)
        {
            std::cout << node->data;
        }
        else if (level > 1)
        {
            formatPrintTree(node->leftNode, level - 1, depth);

            for (size_t j = 0; j < std::pow(2, depth - level - 1); j++)
                std::cout << " ";

            formatPrintTree(node->rightNode, level - 1, depth);
        }
    }
} // namespace tree
