#ifndef _PARSER_H_ // include guard
#define _PARSER_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#include "Tree.h"
#include "Node.h"
#include "Stack.h"
#include "Lexer.h"
#include "Token.h"

namespace parser
{
    class Parser
    {
    private:
        std::vector<std::string> lines;

    public:
        // constructs a parser object from the lines of a file
        Parser(std::vector<std::string> filesLines);

        // parses the lines from the file
        void parseLines();

        // parses a single string line
        void parseLine(std::string line);

        // recursively traverse the tree
        template <class T>
        void formatPrintTree(const node::Node<T> *p, int level, int depth);
        // prints the abstract syntax tree with formatting
        void printTreeHelper(tree::Tree *tree);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        // template <class T>
        node::Node<token::Token> *shuntingYardPostFix(std::vector<token::Token> line);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the pre fix representation of the expression
        // void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);

        // // split line at spaces
        // std::vector<std::string> splitString(std::string line);
        // seperates a string into its token components
        std::vector<token::Token> removeDupWord(std::string str);
    };
} // namespace parser

#endif