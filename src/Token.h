#ifndef _TOKENS_H_
#define _TOKENS_H_

#include "Lexer.h"

namespace token
{
    class Token
    {
    private:
    public:
        lexer::Attribute attribute;
        std::string value;

        Token();

        Token(lexer::Attribute attr, std::string val);

        friend std::ostream &operator<<(std::ostream &os, const Token &m);
    };

    // template <typename T>
    // class Token
    // {
    // private:
    //     // T /* data */;
    //     T attr;
    //     std::string value;

    // public:
    //     Token() {}

    //     Token(lexer::Attribute attr, std::string val)
    //     {
    //         attribute = attr;
    //         value = val;
    //     }

    //     friend std::ostream &operator<<(std::ostream &os, const Token &m)
    //     {
    //         return os << m.value;
    //     }
    // };

} // namespace token

#endif