#ifndef PARSER // include guard
#define PARSER

#include "Tree.hpp"

#include <vector>

namespace p
{
    class Parser
    {
    private:
        std::vector<std::string> tokens;

    public:
        Parser();
        void printTree(tr::Node *p, int level, int depth);
        void printTreeHelper(tr::Tree *tree);
        void parseLine(std::string line);
        tr::Node *shuntingYardPostFix(std::vector<std::string> line);
        void shuntingYardPreFix(std::vector<std::string> line, tr::Tree *tree);
        std::vector<std::string> removeDupWord(std::string str);
        static bool isInteger(const std::string &s);
        static bool isOperator(std::string val);
        static bool isBracket(const char &val);

        static bool isLeftBracket(const char &val);
        static bool isRightBracket(const char &val);
        std::string pop(std::vector<std::string> vec);
        std::string trim(const std::string &str);
    };
} // namespace p

#endif