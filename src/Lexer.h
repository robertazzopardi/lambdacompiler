#ifndef _LEXER_H_ // include guard
#define _LEXER_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>

namespace lexer
{
    const char ADD = '+';
    const char SUB = '-';
    const char MULT = '*';
    const char DIV = '/';
    const char LB = '(';
    const char RB = ')';
    const char EX = '^';
    const char SP = ' ';

    enum class Attribute
    {
        integer,
        lparen,
        rparen,
        opadd,
        opsub,
        opmul,
        opdiv
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

    class Lexer
    {
    private:
        /* data */
    public:
        Lexer(/* args */);
        ~Lexer();

        static bool isOperator(std::string val);

        static bool isBracket(const char &val);

        static bool isLeftBracket(const char &val);

        static bool isRightBracket(const char &val);

        static bool isInteger(const std::string &s);

        // split line at spaces
        static std::vector<std::string> splitString(std::string line);
    };

} // namespace lexer

#endif