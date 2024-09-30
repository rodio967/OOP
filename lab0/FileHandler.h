#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "WordCounter.h"
#include <string>
#include <list>



class FileHandler {
public:
    FileHandler(const std::string& inputFile, const std::string& outputFile);

    bool readLines(std::string& line, bool& error);

    bool saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) const;

private:
    std::string inputFile;
    std::string outputFile;
};

#endif


