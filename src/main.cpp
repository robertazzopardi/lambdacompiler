#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "../include/FileHandler.hpp"
#include "../include/Constants.hpp"
#include "../include/Parser.hpp"
#include "../include/Literal.hpp"
// #include "../include/Tree.hpp"
// #include "../include/BinaryOperation.hpp"

// using namespace B;
// using namespace L;
using namespace P;

int main(int argc, char *argv[])
{
	// FileHandler handler("./tests/testfile.lambda");
	// handler.readFile();
	// std::cout << handler.contents << std::endl;

	// L::Literal<int> num1(1);
	// L::Literal<int> num2(6);

	// L::Literal<char> char1('H');
	// L::Literal<char> char2('Z');

	// B::BinaryOperation<int, char, int> a(num1.value, '+', num2.value);
	// a.result();

	// B::BinaryOperation<int, char, int> b(num1.value, '-', num2.value);
	// b.result();

	// B::BinaryOperation<int, char, int> c(num1.value, '*', num2.value);
	// c.result();

	// B::BinaryOperation<int, char, int> d(num1.value, '/', num2.value);
	// d.result();
	//////////
	const std::string expression = "(1 + 2) + (2 + 3)";
	P::Parser<std::string> parser(expression);
	// parser.evaluateAst();

	// const std::string expression2 = "(102 + 211)";
	// P::Parser<std::string> parser2(expression2);
	// parser2.evaluateAst();
}
