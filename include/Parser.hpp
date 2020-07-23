#ifndef PARSER // include guard
#define PARSER

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Constants.hpp"
#include "BinaryOperation.hpp"

using namespace B;

namespace P
{
    template <typename T>
    class Parser
    {
    private:
        T line;
        std::vector<T> tokens;

    public:
        Parser(std::string line);
        void printTokens();
        void evaluateAst();
    };

    template <typename T>
    Parser<T>::Parser(std::string line)
    {
        Parser<T>::line = line;

        std::istringstream iss(line);
        Parser<T>::tokens = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    }

    template <typename T>
    void Parser<T>::printTokens()
    {
        for (auto &&i : tokens)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void Parser<T>::evaluateAst()
    {
        for (size_t i = 0; i < tokens.size(); i++)
        {
            for (size_t j = 0; j < tokens[i].length(); i++)
            {
                switch (tokens[i][j])
                {
                case C::ADD:
                {
                    std::stringstream l(tokens[i - 1]);
                    std::stringstream r(tokens[i + 1]);
                    int x = 0;
                    l >> x;
                    int y = 0;
                    r >> y;

                    // B::BinaryOperation<int, char, int> a(tokens[i - 1], '+', tokens[i + 1]);
                    B::BinaryOperation<int, char, int> a(x, '+', y);
                    a.result();

                    std::cout << tokens[i - 1] << C::ADD << tokens[i + 1] << std::endl;
                    break;
                }
                case C::SUB:
                {
                    std::cout << tokens[i - 1] << C::SUB << tokens[i + 1] << std::endl;
                    break;
                }
                case C::MULT:
                {
                    std::cout << tokens[i - 1] << C::MULT << tokens[i + 1] << std::endl;
                    break;
                }
                case C::DIV:
                {
                    std::cout << tokens[i - 1] << C::DIV << tokens[i + 1] << std::endl;
                    break;
                }
                default:
                    // std::cout << tokens[i] << std::endl;
                    break;
                }
            }
        }
    }
} // namespace P

#endif