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
        std::string filePath;

    public:
        FileHandler(std::string path);
        ~FileHandler();
        std::vector<std::string> readFilesLines();
        void writeFile(std::string data);
    }; // class FileHandler
} // namespace filesystem

#endif