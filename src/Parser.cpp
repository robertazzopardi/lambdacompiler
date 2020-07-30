#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "../include/Parser.hpp"
#include "../include/Constants.hpp"

using namespace P;
using namespace C;

Parser::Parser()
{
}

void Parser::parseLine(std::string line)
{
    std::vector<std::string> words = removeDupWord(line);

    class Tree *tree = new Tree();
    calculate(words, tree);

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

std::vector<std::string> Parser::removeDupWord(std::string str)
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
        else if (text == "+" || text == "-" || text == "*" || text == "/")
        {
            split.push_back(text);
        }
        else if (isInteger(text))
        {
            split.push_back(text);
        } // not found
    }

    return split;
}

bool Parser::isInteger(const std::string &s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

bool Parser::charIn(const char &val)
{
    return find(C::SIGNS.begin(), C::SIGNS.end(), val) != C::SIGNS.end();
}

void Parser::calculate(std::vector<std::string> tokens, Tree *tree)
{
    if (std::find(tokens.begin(), tokens.end(), "(") == tokens.end() && std::find(tokens.begin(), tokens.end(), ")") == tokens.end())
    {
        auto count = tokens.size() - std::count_if(tokens.begin(), tokens.end(), [](auto a) { return isInteger(a); });
        int j = 0;
        for (size_t i = 0; i < count; i++)
        {
            tree->cmsrLeft(tokens[j++]);
            tree->setValue(tokens[j++]);
            tree->createRight();
            tree->moveRight();
            if (i + 1 == count)
            {
                tree->setValue(tokens[j]);
                break;
            }
        }
        while (tree->curr->parent != nullptr)
        {
            tree->moveAbove();
        }
    }
    else
    {
        // for (auto &&tokens[i] : tokens)
        for (size_t i = 0; i < tokens.size(); i++)

        {
            // std::cout << i << " " << tokens.size() << std::endl;
            // std::cout << tokens[i] << std::endl;
            if (tokens[i] == "(")
            {
                tree->createLeft();
                tree->moveLeft();
            }
            else if (charIn(*tokens[i].c_str()))
            {
                tree->setValue(tokens[i]);
                tree->createRight();
                tree->moveRight();
            }
            else if (isInteger(tokens[i]))
            {
                if (tree->curr->parent == nullptr)
                {
                    tree->cmsrLeft(tokens[i]);
                }

                else if (tree->curr->left == nullptr)
                {
                    // && !tree->curr->parent->data.empty()
                    tree->cmsrLeft(tokens[i]);
                }

                else if (tree->curr->parent->data.empty())
                {

                    tree->setValue(tokens[i]);
                    tree->moveAbove();
                }
                else
                {
                    // std::cout << "fedf" << std::endl;
                }
            }
            else if (tokens[i] == ")")
            {
                // std::cout << i << " " << tokens.size() << std::endl;
                // if (i != tokens.size() - 1)
                // {
                //     std::cout << "fds" << std::endl;
                while (tree->curr->parent != nullptr)
                {
                    tree->moveAbove();
                }
                // }
                // else {
                //     tree->moveAbove
                // }
            }
        }
    }
}
