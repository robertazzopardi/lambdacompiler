#include <string>
#include <fstream>
#include <iostream>
#include "FileHandler.h"

f::FileHandler::FileHandler(std::string path)
{
    FileHandler::filePath = path;
}

f::FileHandler::~FileHandler()
{
}

std::vector<std::string> f::FileHandler::readFilesLines()
{
    std::vector<std::string> lines;
    std::ifstream file(FileHandler::filePath);
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

void f::FileHandler::writeFile(std::string path)
{
}