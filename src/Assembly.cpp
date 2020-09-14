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
    }

    void Assembly::traverseTree(const node::Node<lexer::Token> *node)
    {
        if (node == nullptr)
            return;

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