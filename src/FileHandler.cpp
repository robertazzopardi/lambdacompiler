#include "FileHandler.h"

namespace fhandler
{
    inline const char *_currentPath()
    {
        char *buff = (char *)malloc(FILENAME_MAX);
        // char buff[FILENAME_MAX];
        GetCurrentDir(buff, FILENAME_MAX);
        // printf("Current working dir: %s\n", buff);

        return buff + '/';
    }

    std::string FileHandler::filename = "";
    std::string FileHandler::filepath = "";
    std::string FileHandler::asmfilename = "";

    std::map<std::string, FlagArgs> FileHandler::flags = {
        {"-asm", {false, ""}},
        {"-out", {false, ""}},
        {"-run", {false, ""}}};

    FileHandler::FileHandler()
    {
    }

    FileHandler::~FileHandler()
    {
    }

    std::string FileHandler::trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first)
        {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    std::vector<std::string> FileHandler::readFilesLines(std::string path)
    {
        std::vector<std::string> lines;
        std::ifstream file(path);
        std::string line;

        if (file.is_open())
        {
            while (std::getline(file, line)) // move to the lexer function
            {
                auto b = line.substr(0, line.find("//"));

                if (b != "")
                    lines.push_back(trim(b));
            }
        }
        else
        {
            std::cout << "Unable to open file" << std::endl;
        }

        return lines;
    }

    void FileHandler::writeFile(const std::string filePath, std::string data)
    {
        std::ofstream myfile(filePath);
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

    void FileHandler::parseArgs(int argc, char **argv)
    {
        // check if there is enough args
        if (argc == 1)
        {
            std::cout << "Too Few Arguements" << std::endl;
            exit(0);
        }

        std::vector<std::string> invalidFlags;
        // loop trailing args
        for (size_t i = 1; i < argc; i++)
        {
            std::string arg(argv[i]);

            // look for file to be compiled
            // if found set filename
            auto extensionFound = arg.find(".lambda");
            if (extensionFound != std::string::npos)
            {
                filename = arg;

                std::string path = _currentPath() + arg;
                filepath = path;

                auto extpos = path.find(".lambda");
                if (extpos != std::string::npos)
                {
                    asmfilename = path.replace(extpos, path.size() - 1, ".asm");
                }
                else
                {
                    std::cout << "error" << std::endl;
                }
            }

            // check if flags are valid
            auto it = flags.find(arg);
            if (it != flags.end())
            {
                it->second.isSet = true;
                //
            }
            else
            {
                if (arg != filename)
                {
                    invalidFlags.push_back(arg);
                }
            }
        }

        for (auto &&i : flags)
        {
            if (!i.second.isSet)
            {
                if (i.first == "-asm")
                {
                    i.second.command = "rm " + fhandler::FileHandler::asmfilename;
                }
                else if (i.first == "-out")
                {
                    i.second.command = "rm " + fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.')) + ".o";
                }
            }
            else
            {
                if (i.first == "-run")
                {
                    i.second.command = fhandler::FileHandler::filename.substr(0, fhandler::FileHandler::filename.find('.'));
                }
            }
        }

        if (filename == "")
        {
            std::cout << "Expected A .lambda File" << std::endl;
        }
        else if (invalidFlags.size() != 0)
        {
            std::cout << (invalidFlags.size() == 1 ? "Invalid Arguement: " : "Invalid Arguements: ");
            for (auto &&i : invalidFlags)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        else
        {
        }
    }

} // namespace fhandler