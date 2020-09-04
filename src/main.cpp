#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out

int main(int argc, char *argv[])
{
    filesystem::FileHandler filehandler("/home/rob/Projects/C++/lambda/tests/testfile.lambda");

    parser::Parser parser(filehandler.readFilesLines());
    parser.parseLines();
}
