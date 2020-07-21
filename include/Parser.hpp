#include <string>
#include <vector>

#ifndef PARSER // include guard
#define PARSER

namespace P
{
    template <typename T, typename A>
    class Parser
    {
    private:
        std::vector<T, A> values;

    public:
        Parser(std::vector<T, A> const &values);
    };

    template <typename T, typename A>
    Parser<T, A>::Parser(std::vector<T, A> const &vec)
    {
        Parser<T, A>::values = vec;
    }

} // namespace P

#endif