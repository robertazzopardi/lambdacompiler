#ifndef _PARSER_H_ // include guard
#define _PARSER_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "Tree.h"
#include "Node.h"
#include "Stack.h"

namespace parser
{
    class Parser
    {
    private:
        std::vector<std::string> lines;

    public:
        // constructs a parser object from the lines of a file
        Parser();

        // parses the lines from the file
        void parseLines(std::vector<std::string> filesLines);

        // parses a single string line
        void parseLine(std::string line);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        node::Node<lexer::Token> *shuntingYardPostFix(std::vector<lexer::Token> line);

        void addRemainingOperators(stack::stack<lexer::Token> &operator_stack, stack::stack<node::Node<lexer::Token> *> &output_stack);
    };
} // namespace parser

#endif