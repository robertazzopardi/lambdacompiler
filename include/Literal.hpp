#ifndef LITERAL // include guard
#define LITERAL

namespace l
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
} // namespace l

#endif