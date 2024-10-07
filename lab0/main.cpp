#include "FileHandler.h"
#include "WordCounter.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error there are no three arguments\n";
        return 1;
    }

    FileHandler fileHandler;
    if (!fileHandler.openInfile(argv[1])) {
        std::cerr << "Error can't open file " << argv[1] << std::endl;
        return 2;
    }


    WordCounter wordCounter;
    std::string line;

    while (fileHandler.readLines(line)) {
        wordCounter.processText(line);
    }


    auto sortedWords = wordCounter.getSortedWords();

    if (!fileHandler.openOutfile(argv[2])) {
        std::cerr << "Error can't open file " << argv[2] << std::endl;
        return 4;
    }

    fileHandler.saveToCSV(sortedWords, wordCounter.getTotalWords());

    fileHandler.closeInfile();
    fileHandler.closeOutfile();

    std::cout << "Processing completed.\n";
    return 0;
}

