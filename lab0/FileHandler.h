#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>
#include <string>
#include <list>



class FileHandler {
public:
    bool openInfile(const std::string& file);
    bool openOutfile(const std::string& file);

    bool readLines(std::string& line);

    void saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords);

private:
    std::ifstream inputFile{nullptr};
    std::ofstream outputFile{nullptr};
};

#endif


