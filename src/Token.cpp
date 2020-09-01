
#include "Token.h"

namespace token
{

    Token::Token()
    {
    }

    Token::Token(lexer::Attribute attr, std::string val)
    {
        attribute = attr;
        value = val;
    }

    std::ostream &operator<<(std::ostream &os, const Token &m)
    {
        return os << m.value;
    }
} // namespace token