#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <cctype>


class WordCounter{
public:
    WordCounter(const std::string& inputFileName, const std::string& outputFileName)
            :inputFileName(inputFileName), outputFileName(outputFileName), totalWords(0){}

    void process(){
        readFile();
        sortWords();
        writeCSV();
    }

private:
    std::string inputFileName;
    std::string outputFileName;
    std::map<std::string, int> wordCount;
    int totalWords;
    std::list<std::pair<std::string, int>> sortedWords;

    std::list<std::string> splitIntoWords(const std::string& line){
        std::list<std::string> words;
        std::string word;
        for (char c : line){
            if (std::isalnum(c)){
                word+=std::tolower(c);
            } else if (!word.empty()){
                words.push_back(word);
                word.clear();
            }
        }
        if (!word.empty()){
            words.push_back(word);
        }
        return words;
    }


    void readFile(){
        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open()){
            std::cerr << "Error opening input file.\n";
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)){
            std::list<std::string> words = splitIntoWords(line);
            for (const auto& word : words){
                ++wordCount[word];
                ++totalWords;
            }
        }
        inputFile.close();
    }

    void sortWords(){
        sortedWords = std::list<std::pair<std::string, int>>(wordCount.begin(), wordCount.end());
        sortedWords.sort([](const auto& a, const auto& b){
            return b.second < a.second;
        });
    }


    void writeCSV(){
        std::ofstream outputFile(outputFileName);
        if (!outputFile.is_open()){
            std::cerr << "Error opening output file.\n";
            return;
        }

        outputFile << "Слово, Частота, Частота (%)\n";
        for (const auto& [word, count] : sortedWords){
            double frequencyPercent=(static_cast<double>(count)/totalWords)*100;
            outputFile << word << "," << count << "," << frequencyPercent << "%\n";
        }

        outputFile.close();
    }
};

int main(int argc, char* argv[]){
    if (argc!=3){
        std::cerr << "Error, the number is not equal to 3";
        return 1;
    }

    WordCounter counter(argv[1], argv[2]);
    counter.process();

    return 0;
}
