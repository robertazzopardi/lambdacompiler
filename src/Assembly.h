#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include <vector>
#include <string>
#include <map>

#include "FileHandler.h"
#include "Tree.h"
#include "Lexer.h"

namespace assembly
{
    class Assembly
    {
    private:
        std::string fileContents;
        std::string currInstruction;
        std::string val1;
        std::string val2;
        std::string op;
        std::string function;
        std::string printFunction;
        const std::string includeFunctions = "%include '" + std::string(fhandler::_currentPath()) + "lib/functions.asm'\n\n";
        const std::string globals = "global main\nextern printf\n\n";
        const std::string dataSection = "section .data\n\tsum DQ 0";
        const std::string textSection = "section .text\n\nmain:\n";
        const std::string returnFromMain = "\n\tret";
        const std::string floatFormat = "\n\tfloatfmt db  '%.6g', 10, 0\n\n";
        const std::string integerFormat = "\n\tintegerfmt db '%d', 10, 0\n\n";

        const std::map<std::string, std::string> operatorMap{
            {"+", "_add"},
            {"-", "_sub"},
            {"*", "_mul"},
            {"/", "_div"},
            {"^", "_ipow"}};

    public:
        Assembly();
        ~Assembly();

        // void createAssembly(const node::Node<lexer::Token> *node);
        void createAssembly(const std::vector<tree::Tree *> trees);
        void buildSystemCommands();

        void traverseTree(const node::Node<lexer::Token> *node);
    };
} // namespace assembly

#endif