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
        std::string _nasm = NASM_FLAGS + fhandler::FileHandler::asmfilename;
        system(_nasm.c_str());

        std::string _linker = GCC_FLAGS + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + " " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
        system(_linker.c_str());

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
            textSection += "\timul\t\t\trbx\n";
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

            if (node->leftNode->data.attribute != lexer::Attribute::op && node->leftNode->data.value[0] == '-' && std::stoi(node->rightNode->data.value) % 2 != 1)
                textSection += "\tneg\t\t\trax\n";

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
                if (node->parentNode->data.value != "^")
                {
                    if (node->parentNode != nullptr)
                    {
                        if (node->parentNode->data.value == "/")
                        {
                            textSection += "\txchg\t\t\trax,\trcx\n";
                            textSection += "\tidiv\t\t\trcx\n";
                        }
                        else
                        {
                            textSection += "\t" + opmapsigned.at(node->parentNode->data.value) + "\t\t\trcx,\trax\n";
                        }
                    }
                    else
                    {
                        textSection += "\t" + opmapsigned.at(node->data.value) + "\t\t\trcx,\trax\n";
                    }
                }
            }
        }
        else if (node->leftNode->data.attribute == lexer::Attribute::integer && node->rightNode->data.attribute != lexer::Attribute::integer)
        {
            if (hasDivisor)
            {
                if (node->data.value == "^")
                {
                    // mov rax, -4
                    // cvtsd2si rbx, xmm0
                    // mov r8, rax
                    // mov r9, rbx
                    // call _ipow
                    // neg rax
                    // cvtsi2sd xmm0, rax
                    textSection += "\tmov\t\t\trax,\t" + node->leftNode->data.value + "\n";
                    textSection += "\tcvtsd2si\trbx,\txmm0\n";
                    textSection += "\tmov\t\t\tr8,\trax\n";
                    textSection += "\tmov\t\t\tr9,\trbx\n";
                    textSection += "\tcall\t\t_ipow\n";
                    if (node->leftNode->data.value[0] == '-')
                        textSection += "\tneg\t\t\trax\n";
                    textSection += "\tcvtsi2sd\txmm0,\trax\n";
                }
                else
                {
                    textSection += "\tmov\t\t\trbx,\t" + node->leftNode->data.value + "\n";
                    // if ()
                    textSection += "\tcvtsi2sd\txmm0,\trax\n";
                    textSection += "\tcvtsi2sd\txmm1,\trbx\n";
                    textSection += "\t" + opmapsimd.at(node->data.value) + "\t\txmm0,\txmm1\n";
                    textSection += "\tmovq\t\trcx,\txmm0\n";
                }
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

                if (!firstSum)
                    textSection += "\tcvtsi2sd\txmm0,\trcx\n";

                textSection += "\tcvtsi2sd\txmm1,\trax\n";
                textSection += "\t" + opmapsimd.at(node->data.value) + "\t\txmm0,\txmm1\n";
                // textSection += "\tmovq\t\trcx,\txmm0\n";
                textSection += "\ncvtsd2si\trax,\txmm0\n";
            }
            else if (firstSum)
            {
                // textSection += "\tmov\t\t\trax,\trcx\n";
                textSection += "\tmov\t\t\trbx,\t" + node->rightNode->data.value + "\n";
                chooseFunction(node);
                // textSection += "\tmov\t\t\trcx,\trax\n";
                if (node->data.value == "/")
                {
                    textSection += "\txchg\t\t\trax,\trcx\n";
                    textSection += "\tidiv\t\t\trcx\n";
                }
                else
                {
                    textSection += "\t" + opmapsigned.at(node->data.value) + "\t\t\trcx,\trax\n";
                }
                firstSum = false;
            }
            else
            {
                // textSection += "\tmov\t\t\trax,\trcx\n";
                textSection += "\tmov\t\t\trbx,\t" + node->rightNode->data.value + "\n";
                chooseFunction(node);
                // textSection += "\tmov\t\t\trcx,\trax\n";
                if (node->data.value == "/")
                {
                    textSection += "\txchg\t\t\trax,\trcx\n";
                    textSection += "\tidiv\t\t\trcx\n";
                }
                // else
                // {
                //     textSection += "\t" + opmapsigned.at(node->data.value) + "\t\t\trcx,\trax\n";
                // }
            }
        }
        else if (node->leftNode->data.attribute == lexer::Attribute::op && node->rightNode->data.attribute == lexer::Attribute::op)
        {
            // std::cout << std::endl;
            if (node->data.value == "/")
                textSection += "\tcvtsi2sd\txmm0,\trax\n";
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
            // case lexer::Attribute::intvar:
            //     break;
            // case lexer::Attribute::type:
            //     break;

        case lexer::Attribute::func:
            if (node->data.value == "print")
            {
                if (hasDivisor)
                    printFloat();
                else
                    printInt();
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

    void Assembly::printInt()
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

    void Assembly::printFloat()
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