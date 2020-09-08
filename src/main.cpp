#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    filesystem::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");

    parser::Parser parser(filehandler.readFilesLines());
    parser.parseLines();
=======
	f::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");

	p::Parser parser(filehandler.readFilesLines());
	parser.parseLines();
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
}
