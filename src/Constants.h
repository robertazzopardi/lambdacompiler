#ifndef CONSTANTS // include guard
#define CONSTANTS

#include <vector>
#include <map>
#include <string>

namespace c
{
    // static const std::vector<std::string> SIGNS{"+", "-", "*", "/", "^"};
    const char ADD = '+';
    const char SUB = '-';
    const char MULT = '*';
    const char DIV = '/';
    const char LB = '(';
    const char RB = ')';

    enum class Associates
    {
        none,
        left_to_right,
        right_to_left
    };
    struct info
    {
        int precedence;
        Associates associates;
    };
    static std::map<std::string, info> operators{{"^", {4, Associates::right_to_left}},
                                                 {"*", {3, Associates::left_to_right}},
                                                 {"/", {3, Associates::left_to_right}},
                                                 {"+", {2, Associates::left_to_right}},
                                                 {"-", {2, Associates::left_to_right}}};

    inline bool isOperator(std::string val)
    {
        return operators.count(val) > 0;
    }

    inline bool isBracket(const char &val)
    {
        return LB == val || RB == val;
    }

    inline bool isLeftBracket(const char &val)
    {
        return LB == val;
    }

    inline bool isRightBracket(const char &val)
    {
        return RB == val;
    }

    inline bool isInteger(const std::string &s)
    {
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != SUB) && (s[0] != ADD)))
            return false;

        char *p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }
} // namespace c

#endif