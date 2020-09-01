#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include <string>
#include <sstream>
#include <iostream>

namespace asmembly
{
    static const std::string nl = "\n";
    static const std::string tab = "\t";
    static const std::string sp = " ";
    static const std::string textSection = "section .text\n";
    static const std::string globalStart = "global _start\n";
    static const std::string startLabel = "_start:";
    static const std::string mov_inst = "mov";

    // inline static std::string mov(std::string reg, std::string val)
    // {
    //     std::stringstream ss;
    //     ss << tab << mov_inst << sp << reg << ", " << sp <<
    // }
} // namespace asmembly

#endif