// FileHandler.hpp
#ifndef FILE_HANDLER // include guard
#define FILE_HANDLER

namespace F
{
    class FileHandler
    {
    private:
        /* data */
        std::string filePath;

    public:
        FileHandler(std::string);
        ~FileHandler();
        void readFile();
        void writeFile(std::string);
        std::string contents;
    }; // class FileHandler
} // namespace F

#endif