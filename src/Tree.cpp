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
} // namespace tree