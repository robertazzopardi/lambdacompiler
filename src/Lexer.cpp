#include "Lexer.h"

namespace lexer
{

    Lexer::Lexer()
    {
    }

    Lexer::~Lexer()
    {
    }

    // bool Lexer::isInt(const std::string s)
    // {
    //     // add negative check
    //     std::string t(s);
    //     if (t.at(0) == '-')
    //         t = t.substr(1);
    //     return t.find_first_not_of("0123456789") == std::string::npos;
    // }

    // bool Lexer::isOperator(const std::string val)
    // {
    //     return operators.count(val) > 0;
    // }
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

    std::vector<lexer::Token> Lexer::lex(std::string str)
    {
        std::vector<Token> tokens;

        // for (auto &&text : split(str))
        // {

        //     if (isInteger(text))
        //     {
        //         // Token token(Attribute::integer, text);
        //         Token token = {Attribute::integer, text};
        //         tokens.push_back(token);
        //     }
        //     else if (text.find('(') != std::string::npos)
        //     {
        //         while (text.find('(') != std::string::npos)
        //         {
        //             Token token = {Attribute::lparen, text.substr(0, 1)}; //(Attribute::lparen, text.substr(0, 1));
        //             tokens.push_back(token);
        //             text = text.substr(1, text.length());
        //         }
        //         // Token token(Attribute::lparen, text);
        //         if (text != "")
        //         {
        //             Token token = {Attribute::lparen, text};
        //             tokens.push_back(token);
        //         }

        //     } // found
        //     else if (text.find(')') != std::string::npos)
        //     {
        //         std::reverse(text.begin(), text.end());
        //         while (text.find(')') != std::string::npos)
        //         {
        //             // Token token(Attribute::rparen, text.substr(text.length() - 1, text.length()));
        //             Token token = {Attribute::rparen, text.substr(text.length() - 1, text.length())};
        //             tokens.push_back(token);
        //             text = text.substr(0, text.length() - 1);
        //         }
        //         // Token token(Attribute::rparen, text);
        //         if (text != "")
        //         {
        //             Token token = {Attribute::rparen, text};
        //             tokens.push_back(token);
        //         }
        //     }
        //     else if (isOperator(*text.c_str()))
        //     {
        //         // Token token(Attribute::opadd, text);
        //         Token token = {Attribute::op, text};
        //         tokens.push_back(token);
        //     }

        //     else if (isFunction(text))
        //     {
        //         Token token = {Attribute::func, text};
        //         tokens.push_back(token);
        //     }
        //     else
        //     {
        //         // std::cout << text << std::endl;

        //         // not found
        //         for (auto &&i : text)
        //         {

        //             std::stringstream ss;
        //             std::string s;
        //             ss << i;
        //             ss >> s;
        //             // std::cout << s;

        //             // Token token(Attribute::integer, s);
        //             Token token = {Attribute::integer, s};

        //             tokens.push_back(token);
        //         }
        //     }
        // }

        // remove spaces

        std::cout << str << std::endl;

        std::string funcPlaceholder;
        std::string numberPlaceholder;
        for (auto c : str)
        {
            if (c == SP || c == CM)
            {
                if (numberPlaceholder != "")
                {

                    if (numberPlaceholder.find(PT) != std::string::npos)
                    { // float
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::floatpt, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                    else
                    { // int
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::integer, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                }
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
                // std::cout << c << " ";
                numberPlaceholder += c;
            }
            else if (isalpha(c))
            {
                // std::cout << c << " ";
                funcPlaceholder += c;
            }
            else if (isOperator(c))
            {
                if (numberPlaceholder != "")
                {

                    if (numberPlaceholder.find(PT) != std::string::npos)
                    { // float
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::floatpt, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                    else
                    { // int
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::integer, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                }

                if (funcPlaceholder != "")
                {
                    // std::cout << funcPlaceholder << " ";
                    tokens.push_back({Attribute::func, funcPlaceholder});
                    funcPlaceholder = "";
                }
                // std::cout << c << " ";
                std::string b;
                b += c;
                tokens.push_back({Attribute::op, b});
            }
            else if (isBracket(c))
            {
                if (numberPlaceholder != "")
                {

                    if (numberPlaceholder.find(PT) != std::string::npos)
                    { // float
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::floatpt, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                    else
                    { // int
                        // std::cout << numberPlaceholder << " ";
                        tokens.push_back({Attribute::integer, numberPlaceholder});
                        numberPlaceholder = "";
                    }
                }

                if (funcPlaceholder != "")
                {
                    // std::cout << funcPlaceholder << " ";
                    tokens.push_back({Attribute::func, funcPlaceholder});
                    funcPlaceholder = "";
                }
                // std::cout << c << " ";
                if (isLeftBracket(c))
                {
                    std::string b;
                    b += c;
                    tokens.push_back({Attribute::lparen, b});
                }
                else
                {
                    std::string b;
                    b += c;
                    tokens.push_back({Attribute::rparen, b});
                }
            }
            else
            {
                // std::cout << std::endl
                //           << c << std::endl;
            }
        }

        if (numberPlaceholder != "")
        {

            if (numberPlaceholder.find(PT) != std::string::npos)
            { // float
                // std::cout << numberPlaceholder << " ";
                tokens.push_back({Attribute::floatpt, numberPlaceholder});
                numberPlaceholder = "";
            }
            else
            { // int
                // std::cout << numberPlaceholder << " ";
                tokens.push_back({Attribute::integer, numberPlaceholder});
                numberPlaceholder = "";
            }
        }

        // std::cout << std::endl;
        // for (auto &&i : tokens)
        // {
        //     std::cout << i.value << " ";
        // }
        // std::cout << std::endl;
        // std::cout << std::endl;

        return tokens;
    }

} // namespace lexer