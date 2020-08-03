#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

#include "../include/Parser.hpp"
#include "../include/Constants.hpp"
#include "../include/Tree.hpp"

p::Parser::Parser()
{
}

void p::Parser::parseLine(std::string line)
{
    std::vector<std::string> words = removeDupWord(line);

    class tr::Tree *tree = new tr::Tree();
    shuntingYardPostFix(words, tree);
    // shuntingYardPreFix(words, tree);

    tree->printPreorder(tree->curr);
    std::cout << std::endl;
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> p::Parser::removeDupWord(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);
    std::vector<std::string> out;
    // Traverse through all words
    do
    {
        // Read a word
        std::string word;
        ss >> word;

        // Print the read word
        // cout << word << endl;
        out.push_back(word);
        // While there is more to read
    } while (ss);

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
        else if (isOperator(text))
        {

            split.push_back(text);
        }
        else if (isInteger(text))
        {
            split.push_back(text);
        } // not found
        else
        {
            // std::cout << text;
            for (auto &&i : text)
            {
                std::stringstream ss;
                std::string s;
                // char c = 'a';
                ss << i;
                ss >> s;
                split.push_back(s);
            }
        }
    }

    return split;
}

bool p::Parser::isInteger(const std::string &s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

bool p::Parser::isOperator(std::string val)
{
    return c::operators.count(val) > 0;
}

bool p::Parser::isBracket(const char &val)
{
    return c::LB == val || c::RB == val;
}

bool p::Parser::isLeftBracket(const char &val)
{
    return c::LB == val;
}

bool p::Parser::isRightBracket(const char &val)
{
    return c::RB == val;
}

std::string p::Parser::pop(std::vector<std::string> vec)
{
    auto x = std::move(vec.back());
    vec.pop_back();
    return x;
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
    const T &top() { return base_type::back(); }
    T pop()
    {
        T x = std::move(top());
        base_type::pop_back();
        return x;
    }
    bool empty() { return base_type::empty(); }
};

void p::Parser::shuntingYardPostFix(std::vector<std::string> tokens, tr::Tree *tree)
{
    // std::vector<std::string> output;
    // stack<std::string> stack;
    // for (auto &&token : tokens)
    // {
    //     if (isInteger(token))
    //     {
    //         output.push_back(token);
    //     }
    //     else if (isOperator(token) || isBracket(*token.c_str()))
    //     {
    //         if (!isLeftBracket(*token.c_str()))
    //         {
    //             while (!stack.empty() && ((isRightBracket(*token.c_str()) && !isLeftBracket(*stack.top().c_str())) || (c::operators[stack.top()].precedence > c::operators[token].precedence) || ((c::operators[stack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::left_to_right))))
    //             {
    //                 output.push_back(stack.pop());
    //             }
    //             // If we popped until '(' because token is ')', toss both parens
    //             if (isRightBracket(*token.c_str()))
    //             {
    //                 stack.pop();
    //             }
    //         }
    //         // Everything except ')' --> stack
    //         if (!isRightBracket(*token.c_str()))
    //         {
    //             stack.push(token);
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "";
    //     }
    // }
    // // Anything left on the operator stack just gets moved to the output
    // while (!stack.empty())
    // {
    //     output.push_back(stack.pop());
    // }
    // for (auto &&i : output)
    // {
    //     std::cout << i;
    // }

    stack<std::string> op_stack;
    stack<tr::Node *> exp_stack;

    for (auto &&token : tokens)
    {
        if (isInteger(token))
        {
            exp_stack.push_back(new tr::Node(token));
        }
        else if (isOperator(token) || isBracket(*token.c_str()))
        {
            if (!isLeftBracket(*token.c_str()))
            {
                while (!op_stack.empty() && ((isRightBracket(*token.c_str()) && !isLeftBracket(*op_stack.top().c_str())) || (c::operators[op_stack.top()].precedence > c::operators[token].precedence) || ((c::operators[op_stack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::left_to_right))))
                {
                    // output.push_back(op_stack.pop());
                    std::string op = op_stack.pop();
                    class tr::Node *e2 = exp_stack.pop();
                    class tr::Node *e1 = exp_stack.pop();
                    exp_stack.push(new tr::Node(op, e1, e2));
                }
                // If we popped until '(' because token is ')', toss both parens
                if (isRightBracket(*token.c_str()))
                {
                    op_stack.pop();
                }
            }
            // Everything except ')' --> stack
            if (!isRightBracket(*token.c_str()))
            {
                op_stack.push(token);
            }
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

    // tree->printPreorder(exp_stack.back());
    tree->curr = exp_stack.pop();

    // assert exp_stack.size() == 1,
    //     ('The expression stack is expected to be of size 1 ' 'after applying the Shunting-Yard algorithm. ' + ERROR_MESSAGE)

    //     return exp_stack.pop()
}

void p::Parser::shuntingYardPreFix(std::vector<std::string> tokens, tr::Tree *tree)
{
    stack<std::string> output;
    stack<std::string> operatorStack;

    std::reverse(tokens.begin(), tokens.end());

    for (auto &&token : tokens)
    {
        if (isInteger(token))
        {
            output.push(token);
        }
        else if (isOperator(token) || isBracket(*token.c_str()))
        {
            if (!isRightBracket(*token.c_str()))
            {
                while (!operatorStack.empty() && ((isLeftBracket(*token.c_str()) && !isRightBracket(*operatorStack.top().c_str())) || (c::operators[operatorStack.top()].precedence > c::operators[token].precedence) || ((c::operators[operatorStack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::right_to_left))))
                {
                    output.push(operatorStack.pop());
                }
                // If we popped until '(' because token is ')', toss both parens
                if (isLeftBracket(*token.c_str()))
                {
                    operatorStack.pop();
                }
            }
            // Everything except ')' --> stack
            if (!isLeftBracket(*token.c_str()))
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
