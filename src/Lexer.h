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
    // const char ADD = '+';
    // const char SUB = '-';
    // const char MULT = '*';
    // const char DIV = '/';
    static const char LB = '(';
    static const char RB = ')';
    static const char EX = '^';
    static const char SP = ' ';

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

    // static std::map<Attribute, std::string> attribute{
    //     {Attribute::integer, "int"},
    //     {Attribute::lparen, "("},
    //     {Attribute::rparen, ")"},
    //     {Attribute::opadd, "+"},
    //     {Attribute::opsub, "-"},
    //     {Attribute::opmul, "*"},
    //     {Attribute::opdiv, "/"}};

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

    static std::map<std::string, info> operators{
        {"^", {4, Associates::right_to_left}},
        {"*", {3, Associates::left_to_right}},
        {"/", {3, Associates::left_to_right}},
        {"+", {2, Associates::left_to_right}},
        {"-", {2, Associates::left_to_right}}};

    class Token
    {
    private:
    public:
        Attribute attribute;
        std::string value;

        Token()
        {
        }

        Token(Attribute attr, std::string val)
        {
            attribute = attr;
            value = val;
        }

        friend std::ostream &operator<<(std::ostream &os, const Token &m)
        {
            return os << m.value;
        }
    };

    class Lexer
    {
    private:
    public:
        Lexer();
        ~Lexer();

        static bool isOperator(const std::string val);

        static bool isOperator(char val);

        static bool isBracket(const char &val);

        static bool isLeftBracket(const char &val);

        static bool isRightBracket(const char &val);

        // static bool isInteger(const std::string &s);

        static bool isInt(const std::string s);

        // split line at spaces
        static std::vector<std::string> split(std::string line);

        // seperates a string into its token components
        static std::vector<Token> lex(const std::string str);
    };

} // namespace lexer

#endif