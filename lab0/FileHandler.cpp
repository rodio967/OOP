#include "FileHandler.h"
#include <fstream>
#include <iostream>


FileHandler::FileHandler(const std::string& inputFile, const std::string& outputFile)
        : inputFile(inputFile), outputFile(outputFile) {}

std::list<std::string> FileHandler::readLines() const {
    std::ifstream inFile(inputFile);
    std::list<std::string> lines;
    std::string line;

    if (!inFile) {
        std::cerr << "Error opening input file.\n";
        return lines;
    }

    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    return lines;
}

void FileHandler::saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) const {
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening output file.\n";
        return;
    }

    outFile << "Word,Frequency,Frequency (%)\n";

    for (const auto& [word, count] : sortedWords) {
        double frequencyPercentage = (double)(count) / totalWords * 100.0;
        outFile << word << ',' << count << ',' << frequencyPercentage << '\n';
    }
}
