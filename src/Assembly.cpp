#include "Assembly.h"

namespace assembly
{
    Assembly::Assembly()
    {
    }

    Assembly::~Assembly()
    {
    }

    void Assembly::createAssembly(const std::vector<tree::Tree *> trees)
    {
        fileContents = includeFunctions + globals;

        for (auto &&tree : trees)
        {
            hasDivisor = false;
            traverseTree(tree->root);
        }

        fileContents += dataSection + integerFormat + floatFormat + textSection;
        fileContents += returnFromMain;

        fhandler::FileHandler::writeFile(fhandler::FileHandler::asmfilename, fileContents);

        // assemble the file
        buildSystemCommands();
    }

    void Assembly::buildSystemCommands()
    {
        // nasm ./tests/testfile.asm -f elf64 -o ./tests/testfile.o
        // gcc -no-pie -Wall -Wextra -Werror -o ./tests/testfile ./tests/testfile.o
        //  rm ./tests/testfile.o
        //  ./tests/testfile

        std::string _nasm = "nasm " + fhandler::FileHandler::asmfilename + " -f elf64";
        system(_nasm.c_str());

        std::string _linker = "gcc -no-pie -Wall -Wextra -Werror -o " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + " " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
        system(_linker.c_str());

        // nasm examples/testfile.asm -f elf64 && gcc -no-pie -Wall -Wextra -Werror -o examples/testfile examples/testfile.o && ./examples/testfile
        for (auto &&i : fhandler::FileHandler::flags)
            if (i.second.command != "")
                system(i.second.command.c_str());
    }

    void Assembly::traverseTree(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        traverseTree(node->leftNode);
        traverseTree(node->rightNode);

        // std::cout << node->data.value << " " << std::endl;

        switch (node->data.attribute)
        {
            // case lexer::Attribute::floatpt:

            //     break;

            // case lexer::Attribute::integer:

            //     break;

        case lexer::Attribute::func:
            if (node->data.value == "print")
            {
                if (hasDivisor)
                    textSection += "\tprint_float [sum" + std::to_string(count) + "], floatfmt\n\n";
                else
                    textSection += "\tprint_sum [sum" + std::to_string(count) + "], integerfmt\n\n";
            }
            break;

        case lexer::Attribute::op:
            if (node->data.value == "/")
                hasDivisor = true;
            // left node is number
            // right node is number
            // else
            if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
            {
                if (node->data.value == "^")
                {
                    dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                    sumVariables.push_back("[sum" + std::to_string(count) + "]");

                    textSection += "\tmov r8, " + node->leftNode->data.value + "\n\tmov r9, " + node->rightNode->data.value + "\n";
                    textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

                    textSection += "\tmov [sum" + std::to_string(count) + "], rax\n";
                }
                else
                {
                    dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                    sumVariables.push_back("[sum" + std::to_string(count) + "]");

                    textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + node->rightNode->data.value + ", [sum" + std::to_string(count) + "]\n";
                }
            }

            // left node is number
            // right node not number
            else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute != lexer::Attribute::integer)
            {
                if (node->data.value == "^")
                {
                    // textSection += "\tmov r8, " + sumVariables[sumVariables.size() - 2] + "\n";
                    textSection += "\tmov r8, " + node->leftNode->data.value + "\n";
                    textSection += "\tmov r9, " + sumVariables[sumVariables.size() - 1] + "\n ";
                    textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

                    textSection += "\tmov " + sumVariables[sumVariables.size() - 1] + ", rax\n";
                }
                else
                {
                    dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                    sumVariables.push_back("[sum" + std::to_string(count) + "]");

                    textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", [sum" + std::to_string(count - 1) + "], [sum" + std::to_string(count) + "]\n";
                }
            }

            // left node not number
            // right node is number
            else if (node->leftNode->data.attribute != lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
            {
                if (node->data.value == "^")
                {
                    dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                    sumVariables.push_back("[sum" + std::to_string(count) + "]");

                    // textSection += "\tmov r8, " + node->leftNode->data.value + "\n\tmov r9, " + node->rightNode->data.value + "\n";
                    textSection += "\tmov r8, [sum" + std::to_string(count - 1) + "]\n\tmov r9, " + node->rightNode->data.value + "\n";
                    textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

                    if (node->parentNode->data.value != "print")
                    {
                        // textSection += "\t" + operatorSimpleMap.at(node->parentNode->data.value) + " [sum" + std::to_string(count) + "], rax\n";
                        textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " [sum" + std::to_string(count) + "], rax, " + "[sum" + std::to_string(count) + "]" + "\n";
                    }
                    else
                    {
                        textSection += "\tmov [sum" + std::to_string(count) + "], rax\n";
                    }
                }
                else
                {
                    dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                    sumVariables.push_back("[sum" + std::to_string(count) + "]");

                    textSection += "\t" + operatorMap.at(node->data.value) + " [sum" + std::to_string(count - 1) + "], " + node->rightNode->data.value + ", [sum" + std::to_string(count) + "]\n";
                }
            }

            // left node is operator
            // right node is operator
            else if (node->leftNode->data.attribute == lexer::Attribute::op && node->rightNode->data.attribute == lexer::Attribute::op)
            {
                // std::cout << node->data.value << std::endl;
                // dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                if (node->data.value == "^")
                {
                    textSection += "\tmov r8, " + sumVariables[sumVariables.size() - 2] + "\n";
                    textSection += "\tmov r9, " + sumVariables[sumVariables.size() - 1] + "\n ";
                    textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

                    if (node->parentNode->data.value != "print")
                    {
                        // textSection += "\t" + operatorSimpleMap.at(node->parentNode->data.value) + " [sum" + std::to_string(count) + "], rax\n";
                        textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " [sum" + std::to_string(count) + "], rax, " + "[sum" + std::to_string(count) + "]" + "\n";
                    }
                    else
                    {
                        textSection += "\tmov [sum" + std::to_string(count) + "], rax\n";
                    }
                }
                else
                {
                    textSection += "\t" + operatorMap.at(node->data.value) + " " + sumVariables[sumVariables.size() - 1] + ", " + sumVariables[sumVariables.size() - 2] + ", " + sumVariables[sumVariables.size() - 1] + "\n";
                }
            }

            else
            {
            }
            break;

        default:
            break;
        }
    }

} // namespace assembly