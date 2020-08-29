#ifndef PARSER // include guard
#define PARSER

#include "Tree.h"

#include <vector>

namespace p
{
    class Parser
    {
    private:
        std::vector<std::string> lines;
        std::vector<std::string> tokens;

    public:
        Parser(std::vector<std::string> filesLines);

        // parses the lines from the file
        void parseLines();

        // parses a single string line
        // void parseLine(std::string line);

        // recursively traverse the tree
        void formatPrintTree(tr::Node *p, int level, int depth);
        // prints the abstract syntax tree with formatting
        void printTreeHelper(tr::Tree *tree);

        // parses the tokens using the shunting yard algorithm
        // returns a node with the post fix representation of the expression
        tr::Node *shuntingYardPostFix(std::vector<std::string> line);
        // parses the tokens using the shunting yard algorithm
        // returns a node with the pre fix representation of the expression
        void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);
        // seperates a string into its token components
        std::vector<std::string> removeDupWord(std::string str);

        // std::string trim(const std::string &str);
    };
} // namespace p

#endif