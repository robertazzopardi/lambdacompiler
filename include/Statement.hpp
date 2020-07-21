#ifndef STATEMENT // include guard
#define STATEMENT

namespace S
{
    template <typename T>
    class Statement
    {
    private:
        T line;

    public:
        Statement(T line);
    };

} // namespace S

#endif