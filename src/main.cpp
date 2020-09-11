#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out

int main(int argc, char *argv[])
{

    parser::Parser parser(filesystem::FileHandler::readFilesLines("/home/rob/Projects/C++/lambda/tests/testfile.lambda"));
    parser.parseLines();

    // filesystem::FileHandler::writeFile("/home/rob/Projects/C++/lambda/tests/", "");
}
