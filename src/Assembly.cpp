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
        // const std::string includeFunctions = "%include '" + std::string(fhandler::_currentPath()) + "lib/functions.asm'\n\n";
        // const std::string globals = "global main\nextern printf\n\n";
        // const std::string dataSection = "section .data\n\tsum DQ 0";
        // const std::string textSection = "section .text\n\nmain:\n";
        // const std::string returnFromMain = "\n\tret";
        // const std::string floatFormat = "\n\tfloatfmt db  '%.6g', 10, 0\n\n";
        // const std::string integerFormat = "\n\tintegerfmt db '%d', 10, 0\n\n";

        fileContents = includeFunctions + globals;

        // traverseTree(node);

        for (auto &&tree : trees)
        {
            sumVariables = {};
            traverseTree(tree->root);
            numSums = sumVariables.size();
        }

        fileContents += dataSection + integerFormat + textSection;
        fileContents += returnFromMain;
        // std::cout << std::endl
        //           << fileContents << std::endl;

        fhandler::FileHandler::writeFile(fhandler::FileHandler::asmfilename, fileContents);

        // assemble the file
        buildSystemCommands();
    }

    // void Assembly::createAssembly(const node::Node<lexer::Token> *node)
    // {
    //     fileContents = includeFunctions + globals + dataSection + integerFormat + textSection;
    //     traverseTree(node);
    //     fileContents += returnFromMain;
    //     // std::cout << std::endl
    //     //           << fileContents << std::endl;
    //     fhandler::FileHandler::writeFile(fhandler::FileHandler::asmfilename, fileContents);
    //     // assemble the file
    //     buildSystemCommands();
    // }

    void Assembly::buildSystemCommands()
    {
        // nasm ./tests/testfile.asm -f elf64 -o ./tests/testfile.o
        // gcc -no-pie -Wall -Wextra -Werror -o ./tests/testfile ./tests/testfile.o
        //  rm ./tests/testfile.o
        //  ./tests/testfile

        // std::cout << "nasm " + fhandler::FileHandler::asmfilename + " -f elf64" << std::endl;
        std::string _nasm = "nasm " + fhandler::FileHandler::asmfilename + " -f elf64";
        system(_nasm.c_str());
        // std::cout << _nasm.c_str() << std::endl;

        // std::cout << "gcc -no-pie -Wall -Wextra -Werror -o " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + " " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o" << std::endl;
        std::string _linker = "gcc -no-pie -Wall -Wextra -Werror -o " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + " " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
        system(_linker.c_str());
        // std::cout << _linker.c_str() << std::endl;

        // // std::cout
        // //     << "rm " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o" << std::endl;
        // std::string _rmOutput = "rm " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
        // // system(_rmOutput.c_str());
        // // std::cout << _rmOutput.c_str() << std::endl;

        // // std::cout
        // //     << "rm " + fhandler::FileHandler::asmfilename << std::endl;
        // std::string _rmAsm = "rm " + fhandler::FileHandler::asmfilename;
        // // system(_rmAsm.c_str());
        // // std::cout << _rmAsm.c_str() << std::endl;

        // //
        // std::string _runFile = "./" + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.'));
        // // system(_runFile.c_str());
        // // std::cout << _runFile.c_str() << std::endl;

        for (auto &&i : fhandler::FileHandler::flags)
        {
            if (i.second.command != "")
                system(i.second.command.c_str());
            // std::cout << i.second.command << " " << i.second.isSet << std::endl;
            // if (!i.second.isSet)
            // {
            //     // std::cout << i.first << std::endl;
            //     system(i.second.command.c_str());
            // }
            // else
            // {
            //     // std::cout << "dsdadsadasdasasdas" << std::endl;
            //     system(i.second.command.c_str());
            // }
        }
    }

    void Assembly::traverseTree(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
        {
            return;
        }

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

                // for (size_t i = 0; i < sumVariables.size() - 1; i++)
                // {
                //     std::string lastSum = "[sum" + std::to_string(count - 1) + "]";
                //     if (sumVariables[i] != lastSum)
                //         textSection += "\t_add " + sumVariables.back() + ", " + sumVariables[i] + ", " + sumVariables.back() + "\n";
                // }

                textSection += "\tprint_sum [sum" + std::to_string(count) + "], integerfmt\n\n";
            }
            break;

        case lexer::Attribute::op:

            // add operator to the sums
            // if (node->data.value == "^")
            // {
            //     dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
            //     sumVariables.push_back("[sum" + std::to_string(count) + "]");

            //     textSection += "\tmov r8, " + node->leftNode->data.value + "\n\tmov r9, " + node->rightNode->data.value + "\n";
            //     textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

            //     textSection += "\t" + operatorSimpleMap.at(node->parentNode->data.value) + " [sum" + std::to_string(count) + "], rax\n";
            // }

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
                dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
                sumVariables.push_back("[sum" + std::to_string(count) + "]");

                textSection += "\t" + operatorMap.at(node->data.value) + " [sum" + std::to_string(count) + "], " + node->leftNode->data.value + ", [sum" + std::to_string(count) + "]\n";
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
            else
            {
            }
            break;

        default:
            break;
        }
    }

} // namespace assembly