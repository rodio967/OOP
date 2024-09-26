#include "FileHandler.h"
#include "WordCounter.h"
#include <fstream>
#include <iostream>


FileHandler::FileHandler(const std::string& inputFile, const std::string& outputFile)
        : inputFile(inputFile), outputFile(outputFile) {}


bool FileHandler::readLines(WordCounter& wordCounter) const {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error opening input file.\n";
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        wordCounter.processText(line);
    }
    return true;
}


bool FileHandler::saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) const {
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening output file.\n";
        return false;
    }

    outFile << "Word,Frequency,Frequency (%)\n";

    for (const auto& [word, count] : sortedWords) {
        double frequencyPercentage = (double)(count) / totalWords * 100.0;
        outFile << word << ',' << count << ',' << frequencyPercentage << '\n';
    }
    return true;
}

