#ifndef _STACK_
#define _STACK_

namespace stack
{
    template <typename T>
    struct stack : public std::vector<T>
    {
        using base_type = std::vector<T>;
        T push(const T &x)
        {
            base_type::push_back(x);
            return x;
        }
        const T &top()
        {
            return base_type::back();
        }
        T pop()
        {
            T x = std::move(top());
            base_type::pop_back();
            return x;
        }
        bool empty()
        {
            return base_type::empty();
        }
    };
} // namespace stack

#endif