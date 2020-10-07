#include "FileHandler.h"
#include "Parser.h"

// nasm -felf64 simple.asm && ld simple.o && ./a.out
// /Users/robertazzopardi/_CODE/C++/lambdacompiler/build/lambda_compiler -run -asm /Users/robertazzopardi/_CODE/C++/lambdacompiler/examples/testfile.lambda

int main(int argc, char **argv)
{
    // std::cout << "test" << std::endl;

    fhandler::FileHandler::parseArgs(argc, argv);

    parser::Parser parser;
    // parser.parseLines(filesystem::FileHandler::readFilesLines("/home/rob/Projects/C++/lambda/tests/testfile.lambda"));

    auto lines = fhandler::FileHandler::readFilesLines(fhandler::FileHandler::filepath);
    parser.parseLines(lines);
}
