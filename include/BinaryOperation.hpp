#include <iostream>
#include "Parser.hpp"

#ifndef BINARY_OPERATION // include guard
#define BINARY_OPERATION

namespace B
{
    template <typename T1, typename T2, typename T3>
    class BinaryOperation
    {
    private:
        T1 left;
        T2 sign;
        T3 right;

    public:
        BinaryOperation(T1 left, T2 sign, T3 right);
        void result();
        auto add(int, int);
        auto sub(int, int);
        auto mul(int, int);
        float div(int, int);
    };

    template <typename T1, typename T2, typename T3>
    BinaryOperation<T1, T2, T3>::BinaryOperation(T1 left, T2 sign, T3 right)
    {
        BinaryOperation<T1, T2, T3>::left = left;
        BinaryOperation<T1, T2, T3>::sign = sign;
        BinaryOperation<T1, T2, T3>::right = right;
    }

    template <typename T1, typename T2, typename T3>
    void BinaryOperation<T1, T2, T3>::result()
    {
        switch (sign)
        {
        case '+':
            std::cout << BinaryOperation<T1, T2, T3>::add(left, right) << std::endl;
            break;

        case '-':
            std::cout << BinaryOperation<T1, T2, T3>::sub(left, right) << std::endl;
            break;

        case '*':
            std::cout << BinaryOperation<T1, T2, T3>::mul(left, right) << std::endl;
            break;

        case '/':
            std::cout << BinaryOperation<T1, T2, T3>::div(left, right) << std::endl;
            break;
        default:
            break;
        }
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::add(int x, int y)
    {
        return x + y;
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::sub(int x, int y)
    {
        return x - y;
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::mul(int x, int y)
    {
        return x * y;
    }

    template <typename T1, typename T2, typename T3>
    float BinaryOperation<T1, T2, T3>::div(int x, int y)
    {
        return float(x) / float(y);
    }
} // namespace B

#endif