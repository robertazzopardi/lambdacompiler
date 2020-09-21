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

        fileContents = includeFunctions + globals + dataSection + integerFormat + textSection;
        // traverseTree(node);
        for (auto &&tree : trees)
            traverseTree(tree->root);

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

        // std::cout << node->data.value << " " << std::endl;

        // switch (node->data.attribute)
        // {
        // case lexer::Attribute::func:
        //     if (node->data.value == "print")
        //     {
        //         printFunction = node->data.value;
        //     }
        //     else
        //     {
        //         function = node->data.value;
        //     }
        //     break;
        // case lexer::Attribute::integer:
        //     if (val1 == "")
        //     {
        //         val1 = node->data.value;
        //     }
        //     else
        //     {
        //         val2 = node->data.value;
        //     }
        //     break;
        // case lexer::Attribute::floatpt:
        //     if (val1 == "")
        //     {
        //         val1 = node->data.value;
        //     }
        //     else
        //     {
        //         val2 = node->data.value;
        //     }
        //     break;
        // case lexer::Attribute::op:
        //     switch (*node->data.value.c_str())
        //     {
        //     case '+':
        //         // std::cout << "FGASDJGSHF" << std::endl;
        //         op = node->data.value;
        //         break;

        //     case '-':
        //         // std::cout << "FGASDJGSHF" << std::endl;
        //         op = node->data.value;
        //         break;

        //     case '*':
        //         // std::cout << "FGASDJGSHF" << std::endl;
        //         op = node->data.value;
        //         break;

        //     case '/':
        //         // std::cout << "FGASDJGSHF" << std::endl;
        //         op = node->data.value;
        //         break;

        //     case '^':
        //         // std::cout << "FGASDJGSHF" << std::endl;
        //         op = node->data.value;
        //         break;

        //     default:
        //         break;
        //     }
        //     break;
        // default:
        //     break;
        // }

        // if (op != "" && val2 != "")
        // {
        //     if (op == "^")
        //     {
        //         fileContents += "\tmov r8, " + val1 + "\n\tmov r9, " + val2 + "\n";
        //         fileContents += "\tcall " + operatorMap.at(op) + "\n";
        //         fileContents += "\tmov [sum], rax\n";
        //     }
        //     else
        //     {
        //         fileContents += "\t" + operatorMap.at(op);
        //         fileContents += " " + val1 + ", " + val2 + ", [sum]\n";
        //     }
        //     if (printFunction != "")
        //     {
        //         fileContents += "\tprint_sum [sum], integerfmt\n\n";
        //         printFunction = "";
        //     }
        //     val1 = val2 = op = "";
        // }

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
                // std::cout << "\tprint_sum [sum], integerfmt\n"
                //           << std::endl;
                fileContents += "\tprint_sum [sum], integerfmt\n\n";
            }
            break;

        case lexer::Attribute::op:
            if (node->data.value == "^")
            {
                // std::cout << node->parentNode->data.value << std::endl;
                fileContents += "\tmov r8, " + node->leftNode->data.value + "\n\tmov r9, " + node->rightNode->data.value + "\n";
                fileContents += "\tcall " + operatorMap.at(node->data.value) + "\n";

                // fileContents += "\tadd [sum], rax\n";
                fileContents += "\t" + operatorSimpleMap.at(node->parentNode->data.value) + " [sum], rax\n";
            }
            else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
            {
                // std::cout << node->data.value << " " << node->leftNode->data.value << " " << node->rightNode->data.value << std::endl;
                // std::cout << "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + node->rightNode->data.value + ", [sum]" << std::endl;
                fileContents += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + node->rightNode->data.value + ", [sum]\n";
            }
            else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute != lexer::Attribute::integer)
            {
                // std::cout << node->data.value << " " << node->leftNode->data.value << std::endl;
                // std::cout << "\t" + operatorMap.at(node->data.value) + " [sum], " + node->leftNode->data.value << std::endl;
                fileContents += "\t" + operatorMap.at(node->data.value) + " [sum], " + node->leftNode->data.value + ", [sum]\n";
            }
            else if (node->leftNode->data.attribute != lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
            {
                // std::cout << node->data.value << " " << node->rightNode->data.value << std::endl;
                // std::cout << "\t" + operatorMap.at(node->data.value) + " [sum], " + node->rightNode->data.value << std::endl;
                fileContents += "\t" + operatorMap.at(node->data.value) + " [sum], " + node->rightNode->data.value + ", [sum]\n";
            }
            else
            {
                // std::cout << node->data.value << std::endl;
                carry = node->data.value;
            }
            break;

        default:
            break;
        }
    }

} // namespace assembly