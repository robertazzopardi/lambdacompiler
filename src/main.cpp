#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out

int main(int argc, char **argv)
{
    // std::cout << "test" << std::endl;

    fhandler::FileHandler::parseArgs(argc, argv);

    parser::Parser parser;

    auto lines = fhandler::FileHandler::readFilesLines(fhandler::FileHandler::filepath);
    parser.parseLines(lines);
}
