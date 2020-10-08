#ifndef _LEXER_H_ // include guard
#define _LEXER_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace lexer
{
    static const char LB = '(';
    static const char RB = ')';
    static const char EX = '^';
    static const char SP = ' ';
    static const char CM = ',';
    static const char SC = ';';
    static const char PT = '.';

    enum class Attribute
    {
        integer,
        floatpt,
        lparen,
        rparen,
        op,
        // print
        func
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

    static std::map<const char, info> operators{
        {'^', {4, Associates::right_to_left}},
        {'*', {3, Associates::left_to_right}},
        {'/', {3, Associates::left_to_right}},
        {'%', {3, Associates::left_to_right}},
        {'+', {2, Associates::left_to_right}},
        {'-', {2, Associates::left_to_right}}};

    struct Token
    {
        Attribute attribute;
        std::string value;
    };

    class Lexer
    {
    private:
    public:
        Lexer();
        ~Lexer();

        static bool isOperator(const char val);
        static bool isBracket(const char &val);
        static bool isLeftBracket(const char &val);
        static bool isRightBracket(const char &val);
        static bool isInteger(const std::string &s);
        static bool isFunction(const std::string value);
        // split line at spaces
        static std::vector<std::string> split(std::string line);
        // seperates a string into its token components
        static std::vector<Token> lex(const std::string str);
        static void addNumber(std::string &numberPlaceholder, std::vector<Token> &tokens);
    };

} // namespace lexer

#endif