#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out

int main(int argc, char *argv[])
{
    fhandler::FileHandler::parseArgs(argc, argv);

    parser::Parser parser;
    // parser.parseLines(filesystem::FileHandler::readFilesLines("/home/rob/Projects/C++/lambda/tests/testfile.lambda"));

    auto lines = fhandler::FileHandler::readFilesLines(fhandler::FileHandler::filepath);
    parser.parseLines(lines);
}
