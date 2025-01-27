#include "../include/WordList.hpp"
#include "../include/constants.hpp"
#include <string.h>

WordList::WordList() {
    std::ifstream file(FILE_NAME);
    numWords = getWordCount(file);
    readWords(file);
    file.close();
}

WordList::~WordList() {
    if (words == nullptr){
        return;
    }

    for (int i = 0; i < numWords; i++) {
        if(words[i] != nullptr) {
            delete[] words[i];
        }
    }

    delete[] words;
}

size_t WordList::getWordCount(std::ifstream &file) {
    char word[100];
    int wordCount = 0;
    while (file.good()) {
        wordCount++;
        file >> word;
    }

    file.seekg(0, std::ios::beg);
    return wordCount;
}

void WordList::readWords(std::ifstream &file) {

    words = new char*[numWords];

    for (int i = 0; i < numWords; i++) {
        words[i] = new char[MAX_WORD_LEN];
        file >> words[i];
    }
}


void WordList::getWord(char * wordBuffer) {
    int randWordIndex = rand() % numWords;
    strcpy(wordBuffer, words[randWordIndex]);
}