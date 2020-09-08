<<<<<<< HEAD
#ifndef _PARSER_H_ // include guard
#define _PARSER_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
=======
#ifndef PARSER // include guard
#define PARSER

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#include "Tree.h"
#include "Node.h"

using namespace n;
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f

#include "Tree.h"
#include "Node.h"
#include "Stack.h"
// #include "Lexer.h"

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
<<<<<<< HEAD

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        node::Node<lexer::Token> *shuntingYardPostFix(std::vector<lexer::Token> line);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the pre fix representation of the expression
        // void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);
=======

        // recursively traverse the tree
        template <class T>
        void formatPrintTree(const n::Node<T> *p, int level, int depth);
        // prints the abstract syntax tree with formatting
        void printTreeHelper(tr::Tree *tree);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        template <class T>
        n::Node<T> *shuntingYardPostFix(std::vector<T> line);
        // parses the tokens using the shunting yard algorithm
        // returns a node with the pre fix representation of the expression
        void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);
        // seperates a string into its token components
        std::vector<std::string> removeDupWord(std::string str);
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
    };
} // namespace parser

#endif