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
        fileContents = includeFunctions + NEW_LINE + NEW_LINE;
        fileContents += GLOB_MAIN;
        fileContents += EXT_PRINT + NEW_LINE + NEW_LINE;

        textSection += NEW_LINE + MAIN + NEW_LINE;

        if (RIP_ADDRESS)
            fileContents += RELATIVE_ADDRESSING;

        for (auto &&tree : trees)
        {
            hasDivisor = false;
            firstSum = true;
            traverseTree(tree->root);
        }

        fileContents += dataSection + NEW_LINE;
        fileContents += integerFormat + floatFormat + NEW_LINE + textSection;
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

        std::string _nasm = NASM_FLAGS + fhandler::FileHandler::asmfilename;
        system(_nasm.c_str());

        std::string _linker = GCC_FLAGS + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + " " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
        system(_linker.c_str());

        // nasm examples/testfile.asm -f elf64 && gcc -no-pie -Wall -Wextra -Werror -o examples/testfile examples/testfile.o && ./examples/testfile
        for (auto &&i : fhandler::FileHandler::flags)
            if (i.second.command != "")
                system(i.second.command.c_str());
    }

    void Assembly::chooseFunction(const node::Node<lexer::Token> *node)
    {
        switch (*node->data.value.c_str())
        {
        case '+':
            textSection += "\tadd\t\t\trax,\trbx\n";
            break;

        case '-':
            textSection += "\tsub\t\t\trax,\trbx\n";
            break;

        case '*':
            textSection += "\tmul\t\t\trbx\n";
            break;

        case '/':
            hasDivisor = true;
            textSection += "\tcvtsi2sd\txmm0,\trax\n";
            textSection += "\tcvtsi2sd\txmm1,\trbx\n";
            textSection += "\tdivsd\t\txmm0,\txmm1\n";
            break;

        case '^':
            textSection += "\tmov\t\t\tr8,\trax\n";
            textSection += "\tmov\t\t\tr9,\trbx\n";
            textSection += "\tcall\t\t_ipow\n";
            break;

        case '%':
            textSection += "\txor\t\t\tedx,\tedx\n";
            textSection += "\tdiv\t\t\trbx\n";
            textSection += "\tmov\t\t\trax,\trdx\n";
            break;

        default:
            break;
        }
    }

    void Assembly::chooseInstruction(const node::Node<lexer::Token> *node)
    {
        if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
        {
            // both
            textSection += "\tmov\t\t\trax,\t" + node->leftNode->data.value + "\n";
            textSection += "\tmov\t\t\trbx,\t" + node->rightNode->data.value + "\n";
            chooseFunction(node);

            if (hasDivisor)
            {
            }
            else if (firstSum)
            {
                textSection += "\tmov\t\t\trcx,\trax\n";
                firstSum = false;
            }
            else
            {
                if (node->parentNode != nullptr)
                {
                    textSection += "\t" + opmapsigned.at(node->parentNode->data.value) + "\t\t\trcx,\trax\n";
                }
                else
                {
                    textSection += "\t" + opmapsigned.at(node->data.value) + "\t\t\trcx,\trax\n";
                }
            }
        }
        else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute != lexer::Attribute::integer)
        {
            if (hasDivisor)
            {
                textSection += "\tmov\t\t\trbx,\t" + node->leftNode->data.value + "\n";
                textSection += "\tcvtsi2sd\t\txmm1,\trbx\n";
                textSection += "\t" + opmapsimd.at(node->data.value) + "\t\txmm0,\txmm1\n";
                textSection += "\tmovq\t\t\trcx,\txmm0\n";
            }
            else if (firstSum)
            {
                textSection += "\tmov\t\t\trax,\t" + node->leftNode->data.value + "\n";
                textSection += "\tmov\t\t\trbx,\trcx\n";
                chooseFunction(node);
                textSection += "\tmov\t\t\trcx,\trax\n";
                firstSum = false;
            }
            else
            {
                textSection += "\tmov\t\t\trax,\t" + node->leftNode->data.value + "\n";
                textSection += "\tmov\t\t\trbx,\trcx\n";
                chooseFunction(node);
                textSection += "\tmov\t\t\trcx,\trax\n";
            }
        }
        else if (node->leftNode->data.attribute != lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
        {
            if (hasDivisor)
            {
                textSection += "\tmov\t\t\trax,\t" + node->rightNode->data.value + "\n";
                textSection += "\tcvtsi2sd\txmm1,\trax\n";
                textSection += "\t" + opmapsimd.at(node->data.value) + "\t\txmm0,\txmm1\n";
                textSection += "\tmovq\t\trcx,\txmm0\n";
            }
            else if (firstSum)
            {
                textSection += "\tmov\t\t\trax,\trcx\n";
                textSection += "\tmov\t\t\trbx,\t" + node->rightNode->data.value + "\n";
                chooseFunction(node);
                textSection += "\tmov\t\t\trcx,\trax\n";
                firstSum = false;
            }
            else
            {
                textSection += "\tmov\t\t\trax,\trcx\n";
                textSection += "\tmov\t\t\trbx,\t" + node->rightNode->data.value + "\n";
                chooseFunction(node);
                textSection += "\tmov\t\t\trcx,\trax\n";
            }
        }
        else if (node->leftNode->data.attribute == lexer::Attribute::op && node->rightNode->data.attribute == lexer::Attribute::op)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }

    void Assembly::traverseTree(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

        traverseTree(node->leftNode);
        traverseTree(node->rightNode);

        switch (node->data.attribute)
        {
        case lexer::Attribute::func:
            if (node->data.value == "print")
            {
                if (hasDivisor)
                    printFloat(count);
                else
                    printInt(count);
            }
            break;

        case lexer::Attribute::op:
            if (node->data.value == "/")
                hasDivisor = true;
            chooseInstruction(node);
            break;

        default:
            break;
        }
    }

    // void Assembly::traverseTree(const node::Node<lexer::Token> *node)
    // {
    //     if (node == nullptr)
    //         return;

    //     traverseTree(node->leftNode);
    //     traverseTree(node->rightNode);

    //     // std::cout << node->data.value << " " << std::endl;

    //     switch (node->data.attribute)
    //     {
    //         // case lexer::Attribute::floatpt:
    //         //     break;
    //         // case lexer::Attribute::integer:
    //         //     break;

    //     case lexer::Attribute::func:
    //         if (node->data.value == "print")
    //         {
    //             if (hasDivisor)
    //                 printFloat(count);
    //             else
    //                 printInt(count);
    //         }
    //         break;

    //     case lexer::Attribute::op:
    //         if (node->data.value == "/")
    //             hasDivisor = true;
    //         // left node is number
    //         // right node is number
    //         // else
    //         if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
    //         {
    //             dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";
    //             sumVariables.push_back("[sum" + std::to_string(count) + "]");

    //             if (node->data.value == "^")
    //             {
    //                 textSection += "\tmov r8, " + node->leftNode->data.value + "\n";

    //                 textSection += "\tmov r9, " + node->rightNode->data.value + "\n";

    //                 textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

    //                 textSection += "\tmov " + sumVariables[sumVariables.size() - 1] + ", rax\n";
    //                 // textSection += "\tmov r8, rax\n";
    //             }
    //             else
    //             {
    //                 textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + node->rightNode->data.value + ", " + sumVariables[sumVariables.size() - 1] + "\n";
    //                 // textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + node->rightNode->data.value + ", r8\n";
    //             }
    //         }

    //         // left node is number
    //         // right node not number
    //         else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute != lexer::Attribute::integer)
    //         {
    //             if (node->data.value == "^")
    //             {

    //                 textSection += "\tmov r8, " + node->leftNode->data.value + "\n";

    //                 textSection += "\tmov r9, " + sumVariables[sumVariables.size() - 1] + "\n ";
    //                 // textSection += "\tmov r9, rax\n ";

    //                 textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

    //                 // textSection += "\tmov hhhh, rax\n";
    //             }
    //             else
    //             {
    //                 dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";

    //                 sumVariables.push_back("[sum" + std::to_string(count) + "]");

    //                 textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ", " + sumVariables[sumVariables.size() - 2] + ", " + sumVariables[sumVariables.size() - 1] + "\n";
    //                 // textSection += "\t" + operatorMap.at(node->data.value) + " " + node->leftNode->data.value + ",  r8, r9\n";
    //             }
    //         }

    //         // left node not number
    //         // right node is number
    //         else if (node->leftNode->data.attribute != lexer::Attribute::integer && node->rightNode->data.attribute == lexer::Attribute::integer)
    //         {
    //             dataSection += "\tsum" + std::to_string(++count) + " DQ 0\n";

    //             sumVariables.push_back("[sum" + std::to_string(count) + "]");

    //             if (node->data.value == "^")
    //             {

    //                 textSection += "\tmov r8, " + sumVariables[sumVariables.size() - 2] + "\n";
    //                 // textSection += "\tmov r8, rax\n";

    //                 textSection += "\tmov r9, " + node->rightNode->data.value + "\n";

    //                 textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

    //                 if (node->parentNode->data.value != "print")
    //                 {
    //                     textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " " + sumVariables[sumVariables.size() - 1] + ", rax, " + sumVariables[sumVariables.size() - 1] + "\n";
    //                     // textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " r8, rax, r8\n";
    //                 }
    //                 else
    //                 {
    //                     textSection += "\tmov " + sumVariables[sumVariables.size() - 1] + ", rax\n";
    //                     // textSection += "\tmov r8, rax\n";
    //                 }
    //             }
    //             else
    //             {

    //                 textSection += "\t" + operatorMap.at(node->data.value) + " " + sumVariables[sumVariables.size() - 2] + ", " + node->rightNode->data.value + ", " + sumVariables[sumVariables.size() - 1] + "\n";
    //                 // textSection += "\t" + operatorMap.at(node->data.value) + " r8, " + node->rightNode->data.value + ", r9\n";
    //             }
    //         }

    //         // left node is operator
    //         // right node is operator
    //         else if (node->leftNode->data.attribute == lexer::Attribute::op && node->rightNode->data.attribute == lexer::Attribute::op)
    //         {
    //             if (node->data.value == "^")
    //             {
    //                 textSection += "\tmov r8, rax\n";

    //                 textSection += "\tmov r9, rax\n ";

    //                 textSection += "\tcall " + operatorMap.at(node->data.value) + "\n";

    //                 if (node->parentNode->data.value != "print")
    //                 {
    //                     textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " " + sumVariables[sumVariables.size() - 1] + ", rax, " + sumVariables[sumVariables.size() - 1] + "\n";
    //                     // textSection += "\t" + operatorMap.at(node->parentNode->data.value) + " r8, rax, r8\n";
    //                 }
    //                 else
    //                 {
    //                     textSection += "\tmov " + sumVariables[sumVariables.size() - 1] + ", rax\n";
    //                     // textSection += "\tmov r8, rax\n";
    //                 }
    //             }
    //             else
    //             {
    //                 textSection += "\t" + operatorMap.at(node->data.value) + " " + sumVariables[sumVariables.size() - 1] + ", " + sumVariables[sumVariables.size() - 2] + ", " + sumVariables[sumVariables.size() - 1] + "\n";
    //                 // textSection += "\t" + operatorMap.at(node->data.value) + " r8, r9, rbx\n";
    //             }
    //         }

    //         else
    //         {
    //         }
    //         break;

    //     default:
    //         break;
    //     }
    // }

    void Assembly::printInt(const int count)
    {
        textSection += "\tmov\t\t\trsi,\trcx\n";
        textSection += "\tsub\t\t\trsp,\t8\n";
        if (RIP_ADDRESS)
            textSection += "\tlea\t\t\trdi,\tintegerfmt\n";
        else
            textSection += "\tmov\t\t\trdi,\tintegerfmt\n";
        textSection += "\txor\t\t\trax,\trax\n";
        textSection += "\tcall\t\t_printf\n";
        textSection += "\tadd\t\t\trsp,\t8\n";
        textSection += "\txor\t\t\trdi,\trdi\n";
        textSection += "\n";
    }

    void Assembly::printFloat(const int count)
    {
        // textSection += "\tmovq\t\txmm0,\trcx\n";
        textSection += "\tsub\t\t\trsp,\t8\n";
        if (RIP_ADDRESS)
            textSection += "\tlea\t\t\trdi,\tfloatfmt\n";
        else
            textSection += "\tmov\t\t\trdi,\tfloatfmt\n";
        textSection += "\tmov\t\t\trax,\t1\n";
        textSection += "\tcall\t\t_printf\n";
        textSection += "\tadd\t\t\trsp,\t8\n";
        textSection += "\txor\t\t\teax,\teax\n";
        textSection += "\txor\t\t\tedi,\tedi\n";
        textSection += "\n";
    }

} // namespace assembly