#include "WordCounter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.txt output.csv\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    WordCounter counter(inputFile);
    counter.sortWordsByFrequency();
    counter.saveToCSV(outputFile);

    return 0;
}
