#include <string>
#include <fstream>
#include "../include/FileHandler.hpp"

using namespace F;

FileHandler::FileHandler(std::string path)
{
    FileHandler::filePath = path;
}

FileHandler::~FileHandler()
{
}

std::vector<std::string> FileHandler::readFile()
{
    std::vector<std::string> lines;
    std::ifstream file(FileHandler::filePath);
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

void FileHandler::writeFile(std::string path)
{
}