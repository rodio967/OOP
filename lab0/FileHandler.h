#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <list>


class FileHandler {
public:
    FileHandler(const std::string& inputFile, const std::string& outputFile);

    std::list<std::string> readLines() const;

    void saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) const;

private:
    std::string inputFile;
    std::string outputFile;
};

#endif

