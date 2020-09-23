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
        std::string carry;
        std::string fileContents;
        // std::string currInstruction;
        // std::string val1;
        // std::string val2;
        // std::string op;
        // std::string function;
        // std::string printFunction;
        size_t count = 0;
        int numSums = 0;
        std::vector<std::string> sumVariables;

        const std::string includeFunctions = "%include '" + std::string(fhandler::_currentPath()) + "lib/functions.asm'\n\n";
        const std::string globals = "global main\nextern printf\n\n";
        // const std::string dataSection = "section .data\n\tsum DQ 0";
        std::string dataSection = "section .data\n";
        std::string textSection = "section .text\n\nmain:\n";
        const std::string returnFromMain = "\tret";
        const std::string floatFormat = "\n\tfloatfmt db  '%.6g', 10, 0\n\n";
        const std::string integerFormat = "\n\tintegerfmt db '%d', 10, 0\n\n";

        const std::map<std::string, std::string> operatorMap{
            {"+", "_add"},
            {"-", "_sub"},
            {"*", "_mul"},
            {"/", "_div"},
            {"^", "_ipow"}};

        const std::map<std::string, std::string> operatorSimpleMap{
            {"+", "add"},
            {"-", "sub"},
            {"*", "mul"},
            {"/", "div"},
            {"^", "_ipow"},
            // {"print", "print_sum"}
        };

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