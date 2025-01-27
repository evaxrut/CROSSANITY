#pragma once

#include "Grid.hpp"
#include "WordList.hpp"
#include "../include/constants.hpp"



struct WordInformation {
    Coordinate startCoord;
    char word[MAX_WORD_LEN];
    Orientation orientation;
    char scrambled[MAX_WORD_LEN];
    bool guessed;
};


class Crosswords {
public:

    Grid grid;
    size_t numWords;

    Crosswords();
    ~Crosswords() = default;

    size_t wordsOnCoordinate(Coordinate &coord, WordInformation **words, bool includeGuessed = false);

    bool wordIsOnCoordinate(Coordinate &coord, WordInformation *wordInfo);

private:
    void build();
    void tryInsertWord(char * word);
    bool tryInsertWordToWord(char* word, size_t connectWordNum);
    void scrambleWords();

    Coordinate getInsertStartCoord(
        char *word,
        size_t wordIdx,
        WordInformation &connWordInfo,
        size_t connectWordIdx
    );


    bool tryInsertWordOnIndex(
        char* word, 
        size_t wordIdx, 
        size_t connectWordNum,
        size_t connectWordIdx
    );

    bool canInsertWord(WordInformation &wordInfo, size_t intersectIdx);

    bool inBounds(Coordinate &coord);

    bool inBounds(WordInformation &wordInfo);

    void insertFirstWord(char * word);
    
    void insertWord(WordInformation &wordInfo);
    


    WordList wordlist;
    WordInformation insertedWords[MAX_WORD_LEN];
    
};