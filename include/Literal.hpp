#ifndef LITERAL // include guard
#define LITERAL

#include "visitor.hpp"

using namespace V;

namespace L
{
    template <typename T>
    class Literal
    {
    private:
    public:
        T value;
        Literal(T value);
        T visit(V::Visitor<T> visitor);
    };

    template <typename T>
    Literal<T>::Literal(T value)
    {
        Literal<T>::value = value;
    }

    template <typename T>
    T Literal<T>::visit(V::Visitor<T> visitor)
    {
        return visitor.visitLiteral(this);
    }
} // namespace L

#endif