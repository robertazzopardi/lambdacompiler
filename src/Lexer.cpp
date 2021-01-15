#include "Lexer.h"

namespace lexer
{
    Lexer::Lexer()
    {
    }

    Lexer::~Lexer()
    {
    }

    bool Lexer::isOperator(const char val)
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
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            return false;

        char *p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }

    bool Lexer::isFunction(const std::string value)
    {
        if (value == "print")
            return true;
        else if (value == "sin")
            return true;
        else if (value == "max")
            return true;

        return false;
    }

    std::vector<std::string> Lexer::split(std::string line)
    {
        // Used to split string at spaces;
        std::vector<std::string> out;
        std::istringstream iss(line);
        for (std::string s; iss >> s;)
            out.push_back(s);

        return out;
    }

    void Lexer::addNumber(std::string &numberPlaceholder, std::vector<Token> &tokens)
    {
        if (numberPlaceholder != "")
        {
            if (numberPlaceholder.find(PT) != std::string::npos)
            { // float
                tokens.push_back({Attribute::floatpt, numberPlaceholder});
                numberPlaceholder = "";
            }
            else
            { // int
                tokens.push_back({Attribute::integer, numberPlaceholder});
                numberPlaceholder = "";
            }
        }
    }

    std::vector<lexer::Token> Lexer::lex(std::string str)
    {
        std::vector<Token> tokens;
        std::cout << str << std::endl;

        std::string funcPlaceholder;
        std::string numberPlaceholder;

        for (auto c : str)
        {
            if (c == SP || c == CM)
            {
                addNumber(numberPlaceholder, tokens);
                continue;
            }
            else if (c == PT)
            {
                if (numberPlaceholder != "")
                {
                    numberPlaceholder += c;
                }
                else
                {
                    // const
                }
            }
            else if (isdigit(c))
            {
                numberPlaceholder += c;
            }
            else if (isalpha(c))
            {
                funcPlaceholder += c;
            }
            else if (isOperator(c))
            {
                // handles negative numbers
                // if (numberPlaceholder == "" && (tokens[tokens.size() - 1].attribute != lexer::Attribute::integer || tokens[tokens.size() - 1].attribute != lexer::Attribute::integer))
                if (numberPlaceholder == "" && c == '-' && (tokens[tokens.size() - 1].attribute != lexer::Attribute::integer || tokens[tokens.size() - 1].attribute != lexer::Attribute::integer))
                {
                    // if (c != '^')
                    // if (c == '-')
                    // {
                    numberPlaceholder += c;
                    // }
                    // else
                    // {
                    //     tokens.push_back({Attribute::op, std::string(1, c)});
                    // }
                    continue;
                }

                addNumber(numberPlaceholder, tokens);

                if (funcPlaceholder != "")
                {
                    tokens.push_back({Attribute::func, funcPlaceholder});
                    funcPlaceholder = "";
                }
                tokens.push_back({Attribute::op, std::string(1, c)});
            }
            else if (isBracket(c))
            {
                addNumber(numberPlaceholder, tokens);

                if (funcPlaceholder != "")
                {
                    tokens.push_back({Attribute::func, funcPlaceholder});
                    funcPlaceholder = "";
                }
                if (isLeftBracket(c))
                {
                    tokens.push_back({Attribute::lparen, std::string(1, c)});
                }
                else
                {
                    tokens.push_back({Attribute::rparen, std::string(1, c)});
                }
            }
            else
            {
            }
        }

        // one final time, for remaining items in the number buffer
        addNumber(numberPlaceholder, tokens);

        for (auto &&i : tokens)
        {
            std::cout << i.value << " ";
        }
        std::cout << std::endl;

        return tokens;
    }

} // namespace lexer
