// FileHandler.hpp
#ifndef _FILE_HANDLER_H_ // include guard
#define _FILE_HANDLER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace filesystem
{
    class FileHandler
    {
    private:
    public:
        FileHandler();
        ~FileHandler();
        static std::vector<std::string> readFilesLines(std::string path);
        static void writeFile(std::string path, std::string data);
    }; // class FileHandler
} // namespace filesystem

#endif