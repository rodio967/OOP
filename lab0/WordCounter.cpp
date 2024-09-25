#include "WordCounter.h"
#include <cctype>

WordCounter::WordCounter() : totalWords(0) {}

void WordCounter::processText(const std::list<std::string>& lines) {
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        for (const auto& word : words) {
            ++wordCount[word];
            ++totalWords;
        }
    }
}

std::list<std::pair<std::string, int>> WordCounter::getSortedWords() const {
    std::list<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());

    sortedWords.sort([](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    return sortedWords;
}

int WordCounter::getTotalWords() const {
    return totalWords;
}

std::list<std::string> WordCounter::splitIntoWords(const std::string& line) const {
    std::list<std::string> words;
    std::string word;

    for (char c : line){
        if (std::isalnum(c)){
            word += std::tolower(c);
        }else if (!word.empty()){
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()){
        words.push_back(word);
        word.clear();
    }


    return words;
}
