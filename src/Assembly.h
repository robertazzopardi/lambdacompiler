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
        bool hasDivisor = false;
        std::string fileContents;
        size_t count = 0;
        std::vector<std::string> sumVariables;

        const std::string includeFunctions = "%include '" + std::string(fhandler::_currentPath()) + "lib/functions.asm'\n\n";
        const std::string globals = "global main\nextern printf\n\n";
        std::string dataSection = "section .data\n";
        std::string textSection = "\nsection .text\n\nmain:\n";
        const std::string returnFromMain = "\tret";
        const std::string floatFormat = "\tfloatfmt db '%.6g', 10, 0\n";
        const std::string integerFormat = "\tintegerfmt db '%d', 10, 0\n";

        const std::map<std::string, std::string> operatorMap{
            {"+", "_add"},
            {"-", "_sub"},
            {"*", "_mul"},
            {"/", "_div"},
            {"^", "_ipow"}};

    public:
        Assembly();
        ~Assembly();

        void createAssembly(const std::vector<tree::Tree *> trees);
        void buildSystemCommands();
        void traverseTree(const node::Node<lexer::Token> *node);
    };
} // namespace assembly

#endif