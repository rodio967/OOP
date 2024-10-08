#include "FileHandler.h"
#include <iostream>
#include <list>
#include <string>


bool FileHandler::openInfile(const std::string& file) {
    inputFile.open(file);
    return inputFile.is_open();
}

bool FileHandler::openOutfile(const std::string& file) {
    outputFile.open(file);
    return outputFile.is_open();
}

bool FileHandler::readLines(std::string& line) {
    const auto& new_string = getline(inputFile,line);
    if (inputFile.bad()) {
        return false;
    }
    return new_string ? true : false;
}


void FileHandler::saveToCSV(const std::list<std::pair<std::string, int>>& sortedWords, int totalWords) {
    outputFile << "Word,Frequency,Frequency (%)\n";

    for (const auto& [word, count] : sortedWords) {
        double frequencyPercentage = (double)(count) / totalWords * 100.0;
        outputFile << word << ',' << count << ',' << frequencyPercentage << '\n';
    }
}

void FileHandler::closeInfile() {
    if (inputFile.is_open()) {
        inputFile.close();
    }
}

void FileHandler::closeOutfile() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

