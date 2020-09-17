#include "Assembly.h"

namespace assembly
{
    Assembly::Assembly()
    {
    }

    Assembly::~Assembly()
    {
    }

    void Assembly::createAssembly(const node::Node<lexer::Token> *node)
    {

        fileContents = includeFunctions + globals + dataSection + integerFormat + textSection;
        traverseTree(node);
        fileContents += returnFromMain;
        // std::cout << fileContents << std::endl;

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
        /* first print data of node */
        // std::cout << node->data << " ";
        // std::cout << node->data.value << " " << std::endl;

        if (node->data.attribute == lexer::Attribute::opadd)
        {
            // std::cout << "_add " << std::endl;
            currInstruction = "_add ";
        }
        else if (node->data.attribute == lexer::Attribute::integer)
        {
            // std::cout << "int" << std::endl;
            if (op1 == "")
            {
                op1 = node->data.value + ", ";
            }
            else
            {
                op2 = node->data.value + ", qword [sum]";
            }
        }
        else
        {
            // std::cout << node->data.value << " " << std::endl;
        }

        // add instructions
        if (op2 != "")
        {
            // std::cout << currInstruction + op1 + op2 << std::endl;
            // std::cout << "print_sum qword [sum], integerfmt" << std::endl;
            fileContents += "\t" + currInstruction + op1 + op2 + "\n\t" + "print_sum qword [sum], integerfmt\n";
        }

        traverseTree(node->leftNode);
        traverseTree(node->rightNode);
    }

    static std::string asmAdd(std::string operand1, std::string operand2)
    {
        return "_add " + operand1 + ", " + operand2 + ", qword [sum]";
    }

    static std::string asmPrintInt()
    {
        return "print_sum qword [sum], integerfmt";
    }

    static std::string asmPrintFloat()
    {
        return "print_sum qword [sum], floatfmt";
    }
} // namespace assembly