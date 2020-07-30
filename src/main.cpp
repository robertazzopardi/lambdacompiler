#include "../include/FileHandler.hpp"
#include "../include/Constants.hpp"
#include "../include/Parser.hpp"
#include "../include/Literal.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[])
{
	f::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");
	p::Parser parser;
	for (auto &&i : filehandler.readFile())
	{
		// std::cout << i << std::endl;
		parser.parseLine(i);
	}
}
