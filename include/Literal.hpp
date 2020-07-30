#ifndef LITERAL // include guard
#define LITERAL

namespace L
{
    template <typename T>
    class Literal
    {
    private:
    public:
        T value;
        Literal(T value);
    };

    template <typename T>
    Literal<T>::Literal(T value)
    {
        Literal<T>::value = value;
    }
} // namespace L

#endif