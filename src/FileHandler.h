// FileHandler.hpp
#ifndef _FILE_HANDLER_H_ // include guard
#define _FILE_HANDLER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include <stdlib.h>
#include <stdio.h> /* defines FILENAME_MAX */

//#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace fhandler
{
    const char *_currentPath();

    struct flagArgs
    {
        bool isSet;
        std::string command;
    };

    class FileHandler
    {
    private:
    public:
        static std::string filename;
        static std::string filepath;
        static std::string asmfilename;
        static std::map<std::string, flagArgs> flags;

        FileHandler();
        ~FileHandler();

        static std::string trim(const std::string &str);
        static std::vector<std::string> readFilesLines(std::string path);
        static void writeFile(const std::string filePath, std::string data);

        static void parseArgs(int argc, char **argv);

    }; // class FileHandler
} // namespace fhandler

#endif
