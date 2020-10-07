#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include <vector>
#include <string>
#include <map>

#include "FileHandler.h"
#include "Tree.h"
#include "Lexer.h"
#include "Stack.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#else
//define something for Windows (32-bit only)
#endif

#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#define GLOB_MAIN "global _main\n"
#define MAIN "_main:\n"
#define EXT_PRINT "extern _printf\n"
#define RELATIVE_ADDRESSING "default rel\n\n"
#define NASM_FLAGS "nasm -f macho64 "
#define GCC_FLAGS "gcc -Wall -Wextra -Werror -o "
#else
#error "Unknown Apple platform"
#endif

#elif __linux__
// linux
#define GLOB_MAIN "global main\n"
#define MAIN "main\n"
#define EXT_PRINT "extern printf\n"
#define NASM_FLAGS "nasm -f elf64 "
#define GCC_FLAGS "gcc -no-pie -Wall -Wextra -Werror -o "

#elif __unix__ // all unices not caught above
// Unix

#elif defined(_POSIX_VERSION)
// POSIX

#else
#error "Unknown compiler"
#endif

#ifdef RELATIVE_ADDRESSING
#define RIP_ADDRESS true
#else
#define RIP_ADDRESS false
#endif

namespace assembly
{
    class Assembly
    {
    private:
        stack::stack<std::map<const char *, bool>> registers{};

        bool hasDivisor = false;
        bool firstSum = true;
        std::string fileContents;
        size_t count = 0;
        std::vector<std::string> sumVariables;

        std::string currentSum;

        int stackOffset = 0;

        const std::string NEW_LINE = "\n";
        const std::string TAB = "\t";
        const std::string includeFunctions = "%include '" + std::string(fhandler::_currentPath()) + "lib/functions.asm'";
        std::string dataSection = "section .data\n";
        std::string textSection = "section .text\n";
        const std::string returnFromMain = "\tret\n";
        const std::string floatFormat = "\tfloatfmt db '%.6g', 10, 0\n";
        const std::string integerFormat = "\tintegerfmt db '%d', 10, 0\n";

        // const std::map<std::string, std::string> operatorMap{
        //     {"+", "_add"},
        //     {"-", "_sub"},
        //     {"*", "_mul"},
        //     {"/", "_div"},
        //     {"^", "_ipow"},
        //     {"%", "_mod"}};

        const std::map<std::string, std::string> opmapunsigned{
            {"+", "add"},
            {"-", "sub"},
            {"*", "mul"},
            {"/", "div"},
            {"^", "_ipow"},
            {"%", "_mod"}};

        const std::map<std::string, std::string> opmapsigned{
            {"*", "imul"},
            {"/", "idiv"},
        };

        const std::map<std::string, std::string> opmapsimd{
            {"+", "addsd"},
            {"-", "subsd"},
            {"*", "mulsd"},
            {"/", "divsd"},
            {"^", "_ipow"},
            {"%", "_mod"}};

        std::map<const char *, bool> reg8byte{
            {"rax", false},
            {"rcx", false},
            {"rdx", false},
            {"rbx", false},
            {"rsi", false},
            {"rdi", false},
            {"rsp", false},
            {"rbp", false},
            {"r8", false},
            {"r9", false},
            {"r10", false},
            {"r11", false},
            {"r12", false},
            {"r13", false},
            {"r14", false},
            {"r15", false}};

    public:
        Assembly();
        ~Assembly();

        void createAssembly(const std::vector<tree::Tree *> trees);
        void buildSystemCommands();
        void traverseTree(const node::Node<lexer::Token> *node);

        void printInt(const int count);
        void printFloat(const int count);

        void chooseInstruction(const node::Node<lexer::Token> *node);
        void chooseFunction(const node::Node<lexer::Token> *node);
    };
} // namespace assembly

#endif