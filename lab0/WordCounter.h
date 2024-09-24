#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <map>
#include <list>

class WordCounter {
private:
    std::map<std::string, int> wordCount;
    std::list<std::pair<std::string, int>> sortedWords;

    void splitIntoWords(const std::string& line, std::list<std::string>& words);

public:
    WordCounter(const std::string& inputFile);
    void sortWordsByFrequency();
    void saveToCSV(const std::string& outputFile) const;
};

#endif
