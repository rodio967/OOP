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
    WordCounter wordCounter;
    std::string line;
    bool Error_readtext = false;


    while (fileHandler.readLines(line,Error_readtext)){
        wordCounter.processText(line);
    }

    if (Error_readtext){
        std::cerr << "Error readLines" << std::endl;
        return 2;
    }

    auto sortedWords = wordCounter.getSortedWords();

    if(!fileHandler.saveToCSV(sortedWords, wordCounter.getTotalWords())) {
        std::cout << "Error write to CSV";
        return 3;
    }

    std::cout << "Processing completed.\n";
    return 0;
}

