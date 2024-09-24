#include "WordCounter.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <iostream>

WordCounter::WordCounter(const std::string& inputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error opening input file.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::list<std::string> words;
        splitIntoWords(line, words);
        for (const auto& word : words) {
            ++wordCount[word];
        }
    }

    sortedWords = std::list<std::pair<std::string, int>>(wordCount.begin(), wordCount.end());
}

void WordCounter::splitIntoWords(const std::string& line, std::list<std::string>& words) {
    std::string word;

    for (char c : line){
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }
}

void WordCounter::sortWordsByFrequency() {
    sortedWords.sort([](const auto& a, const auto& b) {
        return b.second < a.second;
    });
}

void WordCounter::saveToCSV(const std::string& outputFile) const {
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening output file.\n";
        return;
    }

    outFile << "Word,Frequency,Frequency (%)\n";
    int totalWords = 0;
    for (const auto& [word, count] : sortedWords) {
        totalWords += count;
    }

    for (const auto& [word, count] : sortedWords) {
        double frequencyPercentage = (double)(count) / totalWords * 100.0;
        outFile << word << ',' << count << ',' << frequencyPercentage << '\n';
    }
}
