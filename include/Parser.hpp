#ifndef PARSER // include guard
#define PARSER

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
// #include <algorithm>

#include "Constants.hpp"
#include "BinaryOperation.hpp"
#include "Tree.hpp"

using namespace B;
using namespace C;
using namespace Tr;

namespace P
{
    template <typename T>
    class Parser
    {
    private:
        // T line;
        int count = 0;
        std::vector<T> tokens;

    public:
        Parser(std::string line);
        void calculate(std::vector<std::string> line, Node *tree, int pos);
        std::vector<std::string> removeDupWord(std::string str);
        bool isInteger(const std::string &s);
        // void printTokens();
        // void evaluateAst();
    };

    template <typename T>
    Parser<T>::Parser(std::string line)
    {
        // Parser<T>::line = line;

        // std::istringstream iss(line);
        // Parser<T>::tokens = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        class Node *root = new Node();
        // root->setData("root");
        std::vector<std::string> words = Parser<T>::removeDupWord(line);
        for (auto &&i : words)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        Parser<T>::calculate(words, root, 0);

        Tr::printPreorder(root);
    }

    template <typename T>
    std::vector<std::string> Parser<T>::removeDupWord(std::string str)
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
        // for (auto &&i : out)
        for (size_t i = 0; i < out.size(); i++)
        {
            if (out[i].find('(') != std::string::npos)
            {
                // split.push_back(out[i].substr(0, 1));
                split.push_back(std::string(out[i].begin(), out[i].begin() + 1));
                // std::cout << "\t" << out[i + 1] << std::endl;
                split.push_back(out[i].substr(1));
            } // found
            else if (out[i].find(')') != std::string::npos)
            {
                // std::cout << "\t" << std::string(out[i].begin(), out[i].end() - 1) << " " << out[i].substr(0, out[i].size() - 1) << std::endl;
                split.push_back(std::string(out[i].begin(), out[i].end() - 1));
                // split
                split.push_back(out[i].substr(out[i].size() - 1));
            } // found
            else if (out[i] == "+" || out[i] == "-" || out[i] == "*" || out[i] == "/")
            {
                split.push_back(out[i]);
            }
            else if (Parser<T>::isInteger(out[i]))
            {
                // std::cout << out[i] << std::endl;
                split.push_back(out[i]);
            } // not found
        }

        // for (auto &&i : split)
        // {
        //     std::cout << i << " ";
        // }
        // for (size_t i = 0; i < split.size(); i++)
        // {
        //     std::cout << split[i] << " ";
        // }

        // return out;
        return split;
    }

    template <typename T>
    void Parser<T>::calculate(std::vector<std::string> tokens, Node *curr, int i)
    {
        std::cout << tokens[i] << std::endl;

        if (tokens[i] == "(")
        {
            curr->left = new Node();
            curr->left->parent = curr;
            // std::cout << i++ << " ";
            Parser<T>::calculate(tokens, curr->left, ++i);
        }
        else if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
        {
            if (curr == NULL)
            {
                class Node *newNode = new Node();
                newNode->left = curr;
                Parser<T>::calculate(tokens, newNode, ++i);
            }
            else
            {
                curr->setData(tokens[i]);

                curr->right = new Node();

                curr->right->parent = curr;

                Parser<T>::calculate(tokens, curr->right, ++i);
            }
        }
        else if (Parser<T>::isInteger(tokens[i]))
        {
            if (curr->parent != NULL)
            {
                curr->setData(tokens[i]);
                Parser<T>::calculate(tokens, curr->parent, ++i);
            }
            else
            {
                curr->left = new Node();
                curr->left->setData(tokens[i]);
                Parser<T>::calculate(tokens, curr, ++i);
            }
        }
        else if (tokens[i] == ")")
        {
            if (curr->parent == NULL)
            {
                class Node *newNode = new Node();
                newNode->left = curr;
                Parser<T>::calculate(tokens, newNode, ++i);
            }
            else
            {

                std::cout << curr->parent->data << std::endl;
                return;
            }
        }
    }

    // template <typename T>
    // void Parser<T>::calculate(std::vector<std::string> lines, Node *root, int pos)
    // {

    //     // for (auto &&i : lines)
    //     for (unsigned int i = pos; i < lines.size(); i++)
    //     {
    //         if (lines[i] == "(")
    //         {
    //             root->left = new Node();
    //             Parser<T>::calculate(std::vector<std::string>(lines.begin() + i, lines.end()), root->left, i);
    //         }
    //         else if (lines[i] == "+" || lines[i] == "-" || lines[i] == "*" || lines[i] == "/")
    //         {
    //             root->setData(lines[i]);
    //             root->right = new Node();
    //             Parser<T>::calculate(std::vector<std::string>(lines.begin() + i, lines.end()), root->right, i);
    //         }
    //         else if (Parser<T>::isInteger(lines[i]))
    //         {
    //             root->setData(lines[i]);
    //             break;
    //         }
    //         else if (lines[i] == ")")
    //         {
    //             break;
    //         }
    //     }

    //     Tr::printPreorder(root);
    // }

    template <typename T>
    inline bool Parser<T>::isInteger(const std::string &s)
    {
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            return false;

        char *p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }

    // template <typename T>
    // void Parser<T>::calculate(std::string line)
    // {
    //     for (size_t i = 0; i < line.length(); i++)
    //     {
    //         if (line[i] == C::LB)
    //         {
    //             B::BinaryOperation<int, char, int> o;
    //             // std::cout << line[i] << " ";
    //             for (size_t j = i + 1; j < line.length() - 1; j++)
    //             {
    //                 std::cout << line[j] << " ";
    //                 // if (line[j])
    //             }
    //         }
    //     }
    //     std::cout << std::endl;
    // }

} // namespace P

#endif