#ifndef SIGN // include guard
#define SIGN

namespace S
{
    template <typename T>
    class Sign
    {
    private:
    public:
        T value;
        Sign(T value);
    };

    template <typename T>
    Sign<T>::Sign(T value)
    {
        Sign<T>::value = value;
    }
} // namespace S

#endif