#ifndef BINARY_OPERATION // include guard
#define BINARY_OPERATION

#include <iostream>
#include "Parser.hpp"
#include "Constants.hpp"

using namespace C;

namespace B
{
    template <typename...>
    class BinaryOperation;

    template <typename T>
    class BinaryOperation<T>
    {
    private:
        T left;
        T sign;
        T right; /* data */

    public:
        BinaryOperation();
    };

    template <typename T>
    BinaryOperation<T>::BinaryOperation()
    {
    }

    template <typename T1, typename T2, typename T3>
    class BinaryOperation<T1, T2, T3>
    {
    private:
    public:
        T1 left;
        T2 sign;
        T3 right;
        BinaryOperation(T1 left, T2 sign, T3 right);
        ~BinaryOperation();
        void result();
        auto add(T1, T2);
        auto sub(T1, T2);
        auto mul(T1, T2);
        auto div(T1, T2);
    };

    template <typename T1, typename T2, typename T3>
    BinaryOperation<T1, T2, T3>::BinaryOperation(T1 left, T2 sign, T3 right)
    {
        BinaryOperation<T1, T2, T3>::left = left;
        BinaryOperation<T1, T2, T3>::sign = sign;
        BinaryOperation<T1, T2, T3>::right = right;
    }

    template <typename T1, typename T2, typename T3>
    BinaryOperation<T1, T2, T3>::~BinaryOperation()
    {
    }

    template <typename T1, typename T2, typename T3>
    void BinaryOperation<T1, T2, T3>::result()
    {
        switch (sign)
        {
        case C::ADD:
            std::cout << BinaryOperation<T1, T2, T3>::add(left, right) << std::endl;
            break;

        case C::SUB:
            std::cout << BinaryOperation<T1, T2, T3>::sub(left, right) << std::endl;
            break;

        case C::MULT:
            std::cout << BinaryOperation<T1, T2, T3>::mul(left, right) << std::endl;
            break;

        case C::DIV:
            std::cout << BinaryOperation<T1, T2, T3>::div(left, right) << std::endl;
            break;

        default:
            break;
        }
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::add(T1 x, T2 y)
    {
        return x + y;
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::sub(T1 x, T2 y)
    {
        return x - y;
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::mul(T1 x, T2 y)
    {
        return x * y;
    }

    template <typename T1, typename T2, typename T3>
    auto BinaryOperation<T1, T2, T3>::div(T1 x, T2 y)
    {
        return float(x) / float(y);
    }
} // namespace B

#endif