// FileHandler.hpp
#ifndef FILE_HANDLER // include guard
#define FILE_HANDLER

#include <vector>
#include <string>

namespace f
{
    class FileHandler
    {
    private:
        /* data */
        std::string filePath;

    public:
        FileHandler(std::string);
        ~FileHandler();
        std::vector<std::string> readFilesLines();
        void writeFile(std::string);
    }; // class FileHandler
} // namespace f

#endif