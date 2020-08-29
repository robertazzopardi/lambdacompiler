#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>

#include "Parser.h"
#include "Constants.h"
#include "Tree.h"

p::Parser::Parser(std::vector<std::string> filesLines)
{
    p::Parser::lines = filesLines;
}

void p::Parser::parseLines()
{
    for (auto &&line : lines)
    {
        std::vector<std::string> words = removeDupWord(line);

        class tr::Tree *tree = new tr::Tree();
        tree->curr = shuntingYardPostFix(words);

        tree->printPreorder(tree->curr);
        std::cout << std::endl;
    }
}

// void p::Parser::parseLine(std::string line)
// {
//     std::vector<std::string> words = removeDupWord(line);

//     class tr::Tree *tree = new tr::Tree();
//     tree->curr = shuntingYardPostFix(words);

//     tree->printPreorder(tree->curr);
//     std::cout << std::endl;
//     // printTreeHelper(tree);
// }

void p::Parser::printTreeHelper(tr::Tree *tree)
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

void p::Parser::formatPrintTree(tr::Node *node, int level, int depth)
{
    if (node == nullptr)
        return;

    if (level == 1)
    {
        std::cout << node->data;
    }
    else if (level > 1)
    {
        formatPrintTree(node->left, level - 1, depth);
        // std::cout << "x";
        for (size_t j = 0; j < std::pow(2, depth - level - 1); j++)
            std::cout << " ";

        formatPrintTree(node->right, level - 1, depth);
    }
}

// std::string trim(const std::string &str)
// {
//     size_t first = str.find_first_not_of(' ');
//     if (std::string::npos == first)
//     {
//         return str;
//     }
//     size_t last = str.find_last_not_of(' ');
//     return str.substr(first, (last - first + 1));
// }

std::vector<std::string> p::Parser::removeDupWord(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);
    std::vector<std::string> out;
    // Traverse through all words
    std::string token;
    while (ss >> token)
        out.push_back(token);

    //---------------
    std::vector<std::string> split;
    for (auto &&text : out)
    {
        if (text.find('(') != std::string::npos)
        {
            while (text.find('(') != std::string::npos)
            {
                split.push_back(text.substr(0, 1));
                text = text.substr(1, text.length());
            }
            split.push_back(text);

        } // found
        else if (text.find(')') != std::string::npos)
        {
            std::reverse(text.begin(), text.end());
            while (text.find(')') != std::string::npos)
            {
                split.push_back(text.substr(text.length() - 1, text.length()));
                text = text.substr(0, text.length() - 1);
            }
            split.push_back(text);

        } // found
        else if (c::isOperator(text) || c::isInteger(text))
        {
            split.push_back(text);
        }
        else
        {
            // not found
            for (auto &&i : text)
            {
                std::stringstream ss;
                std::string s;
                ss << i;
                ss >> s;

                split.push_back(s);
            }
        }
    }

    return split;
}

template <typename T>
struct stack : public std::vector<T>
{
    using base_type = std::vector<T>;
    T push(const T &x)
    {
        base_type::push_back(x);
        return x;
    }
    const T &top()
    {
        return base_type::back();
    }
    T pop()
    {
        T x = std::move(top());
        base_type::pop_back();
        return x;
    }
    bool empty()
    {
        return base_type::empty();
    }
};

tr::Node *p::Parser::shuntingYardPostFix(std::vector<std::string> tokens)
{
    stack<std::string> op_stack;
    stack<tr::Node *> exp_stack;

    for (auto &&token : tokens)
    {
        if (c::isInteger(token))
        {
            exp_stack.push_back(new tr::Node(token));
        }
        else if (c::isOperator(token) || c::isBracket(*token.c_str()))
        {
            if (!c::isLeftBracket(*token.c_str()))
            {
                while (!op_stack.empty() && ((c::isRightBracket(*token.c_str()) && !c::isLeftBracket(*op_stack.top().c_str())) || (c::operators[op_stack.top()].precedence > c::operators[token].precedence) || ((c::operators[op_stack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::left_to_right))))
                {
                    // output.push_back(op_stack.pop());
                    std::string op = op_stack.pop();
                    class tr::Node *e2 = exp_stack.pop();
                    class tr::Node *e1 = exp_stack.pop();
                    exp_stack.push(new tr::Node(op, e1, e2));
                }
                // If we popped until '(' because token is ')', toss both parens
                if (c::isRightBracket(*token.c_str()))
                    op_stack.pop();
            }
            // Everything except ')' --> stack
            if (!c::isRightBracket(*token.c_str()))
                op_stack.push(token);
        }
        else
        {
            std::cout << "";
        }
    }
    while (!op_stack.empty())
    {
        std::string op = op_stack.pop();
        class tr::Node *e2 = exp_stack.pop();
        class tr::Node *e1 = exp_stack.pop();
        exp_stack.push(new tr::Node(op, e1, e2));
        // output.push_back(stack.pop());
    }

    return exp_stack.pop();
}

void p::Parser::shuntingYardPreFix(std::vector<std::string> tokens, tr::Tree *tree)
{
    stack<std::string> output;
    stack<std::string> operatorStack;

    std::reverse(tokens.begin(), tokens.end());

    for (auto &&token : tokens)
    {
        if (c::isInteger(token))
        {
            output.push(token);
        }
        else if (c::isOperator(token) || c::isBracket(*token.c_str()))
        {
            if (!c::isRightBracket(*token.c_str()))
            {
                while (!operatorStack.empty() && ((c::isLeftBracket(*token.c_str()) && !c::isRightBracket(*operatorStack.top().c_str())) || (c::operators[operatorStack.top()].precedence > c::operators[token].precedence) || ((c::operators[operatorStack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::right_to_left))))
                {
                    output.push(operatorStack.pop());
                }
                // If we popped until '(' because token is ')', toss both parens
                if (c::isLeftBracket(*token.c_str()))
                {
                    operatorStack.pop();
                }
            }
            // Everything except ')' --> stack
            if (!c::isLeftBracket(*token.c_str()))
            {
                operatorStack.push(token);
            }
        }
        else
        {
            std::cout << "";
        }
    }
    // Anything left on the operator stack just gets moved to the output

    while (!operatorStack.empty())
    {
        output.push_back(operatorStack.pop());
    }

    std::reverse(output.begin(), output.end());
    for (auto &&i : output)
    {
        std::cout << i;
    }
}
