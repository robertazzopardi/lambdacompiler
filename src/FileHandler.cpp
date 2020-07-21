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

void FileHandler::readFile()
{
    std::ifstream file(FileHandler::filePath);
    std::string line;
    while (std::getline(file, line))
    {
        FileHandler::contents.append(line).append("\n");
    }
}

void FileHandler::writeFile(std::string path)
{
}