#include "WordCounter.h"
#include <cctype>

void WordCounter::processText(const std::string& line) {
    std::list<std::string> words = splitIntoWords(line);
    for (const auto& word : words) {
        wordCount[word]++;
        totalWords++;
    }
}


std::list<std::pair<std::string, int>> WordCounter::getSortedWords() const {
    std::list<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());

    sortedWords.sort([](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
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

    for (char c : line) {
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
        word.clear();
    }


    return words;
}

