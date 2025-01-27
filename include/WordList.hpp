#pragma once
#include <fstream>
#include <cstddef>
#include "types.hpp"


class WordList {
public:


    WordList();
    ~WordList();

    void getWord(char * wordBuffer);

private:
    size_t getWordCount(std::ifstream &file);
    void readWords(std::ifstream &file);

    char **words;
    size_t numWords;

};