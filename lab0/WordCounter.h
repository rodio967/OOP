#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>
#include <list>
#include <map>


class WordCounter {
public:
    void processText(const std::string& line);

    std::list<std::pair<std::string, int>> getSortedWords() const;

    int getTotalWords() const;

private:
    std::map<std::string, int> wordCount;
    int totalWords{0};

    std::list<std::string> splitIntoWords(const std::string& line) const;
};

#endif

