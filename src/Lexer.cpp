#include <sstream>
#include <algorithm>
#include <string>

#include "Lexer.h"

namespace lexer
{

    Lexer::Lexer()
    {
    }

    Lexer::~Lexer()
    {
    }

    bool Lexer::isOperator(std::string val)
    {
        return operators.count(val) > 0;
    }

    bool Lexer::isBracket(const char &val)
    {
        return LB == val || RB == val;
    }

    bool Lexer::isLeftBracket(const char &val)
    {
        return LB == val;
    }

    bool Lexer::isRightBracket(const char &val)
    {
        return RB == val;
    }

    bool Lexer::isInteger(const std::string &s)
    {
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != SUB) && (s[0] != ADD)))
            return false;

        char *p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }

    std::vector<std::string> Lexer::splitString(std::string line)
    {
        // Used to split string at spaces;
        std::vector<std::string> out;
        std::istringstream iss(line);
        for (std::string s; iss >> s;)
            out.push_back(s);

        return out;
    }

} // namespace lexer