#include "Lexer.h"

namespace lexer
{

    Lexer::Lexer()
    {
    }

    Lexer::~Lexer()
    {
    }

    bool Lexer::isInt(const std::string s)
    {
        // add negative check
        std::string t(s);
        if (t.at(0) == '-')
            t = t.substr(1);
        return t.find_first_not_of("0123456789") == std::string::npos;
    }

    bool Lexer::isOperator(const std::string val)
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

    // bool Lexer::isInteger(const std::string &s)
    // {
    //     if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    //         return false;

    //     char *p;
    //     strtol(s.c_str(), &p, 10);

    //     return (*p == 0);
    // }

    std::vector<std::string> Lexer::split(std::string line)
    {
        // Used to split string at spaces;
        std::vector<std::string> out;
        std::istringstream iss(line);
        for (std::string s; iss >> s;)
            out.push_back(s);

        return out;
    }

    std::vector<lexer::Token> Lexer::lex(std::string str)
    {
        std::vector<Token> tokens;
        for (auto &&text : split(str))
        {
            if (text.find('(') != std::string::npos)
            {
                while (text.find('(') != std::string::npos)
                {
                    Token token(Attribute::lparen, text.substr(0, 1));
                    tokens.push_back(token);
                    text = text.substr(1, text.length());
                }
                Token token(Attribute::lparen, text);
                tokens.push_back(token);

            } // found
            else if (text.find(')') != std::string::npos)
            {
                std::reverse(text.begin(), text.end());
                while (text.find(')') != std::string::npos)
                {
                    Token token(Attribute::rparen, text.substr(text.length() - 1, text.length()));
                    tokens.push_back(token);
                    text = text.substr(0, text.length() - 1);
                }
                Token token(Attribute::rparen, text);
                tokens.push_back(token);
            }
            else if (isOperator(text))
            {
                Token token(Attribute::opadd, text);
                tokens.push_back(token);
            }
            else if (isInt(text))
            {
                Token token(Attribute::integer, text);
                tokens.push_back(token);
            }
            else
            {
                // not found
                for (auto &&i : text)
                {
                    std::stringstream ss;
                    std::string s;
                    ss << i;
                    ss >> s;
                    std::cout << s;

                    Token token(Attribute::integer, s);

                    tokens.push_back(token);
                }
            }
        }

        return tokens;
    }

} // namespace lexer