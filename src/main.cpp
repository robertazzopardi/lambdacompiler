#include "FileHandler.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
	f::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");

	p::Parser parser(filehandler.readFilesLines());
	parser.parseLines();
}
