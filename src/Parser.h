#ifndef _PARSER_H_ // include guard
#define _PARSER_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "Tree.h"
#include "Node.h"
#include "Stack.h"
#include "Lexer.h"

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

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        node::Node<lexer::Token> *shuntingYardPostFix(std::vector<lexer::Token> line);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the pre fix representation of the expression
        // void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);
    };
} // namespace parser

#endif