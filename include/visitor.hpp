#ifndef VISITOR // include guard
#define VISITOR

namespace V
{
    template <typename T>
    class Visitor
    {
    private:
    public:
        Visitor();
        T visitBinary();
        T visitLiteral();
    };

    template <typename T>
    Visitor<T>::Visitor()
    {
    }

    template <typename T>
    T Visitor<T>::visitBinary()
    {
    }

    template <typename T>
    T Visitor<T>::visitLiteral()
    {
    }
} // namespace V

#endif