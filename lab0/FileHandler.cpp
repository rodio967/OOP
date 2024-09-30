#include "FileHandler.h"
#include <fstream>
#include <iostream>


FileHandler::FileHandler(const std::string& inputFile, const std::string& outputFile)
        : inputFile(inputFile), outputFile(outputFile) {}


bool FileHandler::readLines(std::string& line,bool& error){
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error opening input file.\n";
        error = true;
        return false;
    }

    const auto& new_string = getline(inFile,line);
    return new_string ? true : false;
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

