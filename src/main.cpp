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

using namespace P;
using namespace F;

int main(int argc, char *argv[])
{
	F::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");
	P::Parser parser;
	for (auto &&i : filehandler.readFile())
	{
		// std::cout << i << std::endl;
		parser.parseLine(i);
	}
}
