#include "FileHandler.h"

namespace filesystem
{

    FileHandler::FileHandler(std::string path)
    {
        filePath = path;
    }

    FileHandler::~FileHandler()
    {
    }

    std::vector<std::string> FileHandler::readFilesLines()
    {
        std::vector<std::string> lines;
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("//") == std::string::npos)
            {
                lines.push_back(line);
            }
        }
        return lines;
    }

    void FileHandler::writeFile(std::string path)
    {
    }
} // namespace filesystem