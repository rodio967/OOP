#include "FileHandler.h"
#include "WordCounter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error there are no three arguments\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    FileHandler fileHandler(inputFile, outputFile);

    std::list<std::string> lines = fileHandler.readLines();

    if (lines.empty()) {
        std::cerr << "No lines to process.\n";
        return 1;
    }

    WordCounter wordCounter;

    wordCounter.processText(lines);

    auto sortedWords = wordCounter.getSortedWords();

    fileHandler.saveToCSV(sortedWords, wordCounter.getTotalWords());

    std::cout << "Processing completed.\n";
    return 0;
}
