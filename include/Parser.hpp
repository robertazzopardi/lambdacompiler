#ifndef PARSER // include guard
#define PARSER

#include "Tree.hpp"

using namespace Tr;

namespace P
{
    class Parser
    {
    private:
        std::vector<std::string> tokens;

    public:
        Parser();
        void parseLine(std::string line);
        void calculate(std::vector<std::string> line, Tree *tree);
        std::vector<std::string> removeDupWord(std::string str);
        static bool isInteger(const std::string &s);
        static bool charIn(const char &val);
        std::string trim(const std::string &str);
    };
} // namespace P

#endif