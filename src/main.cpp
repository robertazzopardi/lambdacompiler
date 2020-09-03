#include "FileHandler.h"
#include "Parser.h"

// int ipow(int x, unsigned n)
// {
//     int result = 1;
//     while (n)
//     {
//         if (n & 1)
//             result *= x;
//         n >>= 1;
//         x *= x;
//     }
//     return result;
// }

//   Function exp_by_squaring_iterative(x, n)
//     if n < 0 then
//       x := 1 / x;
//       n := -n;
//     if n = 0 then return 1
//     y := 1;
//     while n > 1 do
//       if n is even then
//         x := x * x;
//         n := n / 2;
//       else
//         y := x * y;
//         x := x * x;
//         n := (n – 1) / 2;
//     return x * y

auto exp_square(int x, int n)
{
    if (n < 0)
    {
        x = 1 / x;
        n *= -1;
    }
    if (n == 0)
    {
        return 1;
    }
    int y = 1;
    while (n > 1)
    {
        if (n % 2 == 0)
        {
            x *= x;
            n = n / 2;
        }
        else
        {
            y *= x;
            x *= x;
            n = (n - 1) / 2;
        }
    }

    return x * y;
}

int main(int argc, char *argv[])
{
    // filesystem::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");

    // parser::Parser parser(filehandler.readFilesLines());
    // parser.parseLines();

    std::cout << exp_square(2, 4) << std::endl;
}
