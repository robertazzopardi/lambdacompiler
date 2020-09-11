#include "FileHandler.h"

namespace filesystem
{

    FileHandler::FileHandler()
    {
    }

    FileHandler::~FileHandler()
    {
    }

    std::vector<std::string> FileHandler::readFilesLines(std::string path)
    {
        std::vector<std::string> lines;
        std::ifstream file(path);
        std::string line;

        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                if (line.find("//") == std::string::npos)
                {
                    lines.push_back(line);
                }
            }
        }
        else
        {
            std::cout << "Unable to open file" << std::endl;
        }

        return lines;
    }

    void FileHandler::writeFile(std::string path, std::string data)
    {
        const std::string assemblyFileName = "assembly.asm";

        std::ofstream myfile(path + assemblyFileName);
        if (myfile.is_open())
        {
            myfile << data;
            myfile.close();
        }
        else
        {
            std::cout << "Unable to open file";
        }
    }
} // namespace filesystem