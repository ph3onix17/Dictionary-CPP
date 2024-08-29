#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

//defin struct.
struct Word {
    std::string name;
    std::string type;
    std::string definition;
};

// case - sensitive converter
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

//function > load the dic. file
bool loadDictionary(const std::string& filename, std::vector<Word>& dictionary) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    Word currentWord;
    std::string line;
    while (getline(file, line)) {
        if (line.substr(0, 6) == "Type: ") {
            currentWord.type = line.substr(6);
        } else if (line.substr(0, 12) == "Definition: ") {
            currentWord.definition = line.substr(12);
        } else if (line.substr(0, 6) == "Word: ") {
            currentWord.name = line.substr(6);
            dictionary.push_back(currentWord);
        }
    }

    file.close();
    return true;
}

//function > search word
void searchDictionary(const std::vector<Word>& dictionary, const std::string& searchWord) {
    std::string lowerSearchWord = toLowerCase(searchWord);
    bool found = false;

    for (const auto& word : dictionary) {
        if (toLowerCase(word.name) == lowerSearchWord) {
            std::cout << "Word: " << word.name << std::endl;
            std::cout << "Type: " << word.type << std::endl;
            std::cout << "Definition: " << word.definition << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Word not found." << std::endl;
    }
}

int main() {
    std::vector<Word> dictionary;
    //methana file locationa maru krnn
    std::string filename = "C:\\Users\\Asus\\Downloads\\training game\\c++ dictionary\\DictionaryHelper.txt";
    
    if (!loadDictionary(filename, dictionary)) {
        return 1; // Exit if dictionary loading fails
    }

    std::string inputWord;
    while (true) {
        std::cout << "Enter a word to search (or type 'exit' to quit): ";
        std::getline(std::cin, inputWord);
        
        if (toLowerCase(inputWord) == "exit") {
            break;
        }

        //search the word
        searchDictionary(dictionary, inputWord);
    }

    return 0;
}