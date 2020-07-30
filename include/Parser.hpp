#ifndef PARSER // include guard
#define PARSER

#include "Tree.hpp"

namespace p
{
    class Parser
    {
    private:
        std::vector<std::string> tokens;

    public:
        Parser();
        void parseLine(std::string line);
        void calculate(std::vector<std::string> line, tr::Tree *tree);
        std::vector<std::string> removeDupWord(std::string str);
        static bool isInteger(const std::string &s);
        static bool charIn(const char &val);
        static bool isBracket(const char &val);
        std::string trim(const std::string &str);
    };
} // namespace p

#endif