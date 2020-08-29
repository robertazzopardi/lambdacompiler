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
    enum class Operators
    {

    };
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
} // namespace c

#endif