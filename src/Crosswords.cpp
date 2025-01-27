#include <string.h>
#include "../include/Crosswords.hpp"
#include "../include/utils.hpp"
#include "../include/types.hpp"

Crosswords::Crosswords(): grid(GRID_HEIGHT, GRID_WIDTH){
    build();
}

size_t Crosswords::wordsOnCoordinate(Coordinate &coord, WordInformation **words, bool includeGuessed) {

    size_t found = 0;
    for (size_t i = 0; i < numWords; i++) {
        if(wordIsOnCoordinate(coord, &insertedWords[i])) {
            if(!includeGuessed && insertedWords[i].guessed) {
                continue;
            }
            words[found] = &insertedWords[i];
            found++;
        }
    }
    return found;
}

bool Crosswords::wordIsOnCoordinate(Coordinate &coord, WordInformation *wordInfo) {
    size_t wordLen = strlen(wordInfo->word);

    if (wordInfo->orientation == Orientation::HORIZONTAL) {
        if (coord.row != wordInfo->startCoord.row) {
            return false;
        }
        if (coord.col < wordInfo->startCoord.col || coord.col >= wordInfo->startCoord.col + wordLen) {
            return false;
        }
    } else {
        if (coord.col != wordInfo->startCoord.col) {
            return false;
        }
        if (coord.row < wordInfo->startCoord.row || coord.row >= wordInfo->startCoord.row + wordLen) {
            return false;
        }
    }
    return true;
}

void Crosswords::build() {

    while (true) {
        numWords = 0;
        grid.reset();

        int numWordsToAdd = utils::getRandomNumber(MIN_WORDS, MAX_WORDS);

        size_t tries = 0;
        while (numWords < numWordsToAdd && tries < MAX_TRIES){
            char word[MAX_WORD_LEN];
            wordlist.getWord(word);
            tryInsertWord(word);
            tries ++;
        }

        if (numWords == numWordsToAdd) {
            break;
        }
    }

    scrambleWords();
}

void Crosswords::scrambleWords() {
    for (size_t i = 0; i < numWords; i++) {
        strcpy(insertedWords[i].scrambled, insertedWords[i].word);
        utils::scrambleWord(insertedWords[i].scrambled);
    }
}




void Crosswords::tryInsertWord(char * word){

    if (numWords == 0){
        insertFirstWord(word);
        return;
    }


    for (size_t i = 0; i < numWords; i++) {
        if(tryInsertWordToWord(word, i)) {
            return;
        }
    }
}

bool Crosswords::tryInsertWordToWord(char * word, size_t connectWordNum) {
    size_t wordLen = strlen(word);
    size_t connectWordLen = strlen(insertedWords[connectWordNum].word);

    for (size_t wordIdx = 0; wordIdx < wordLen; wordIdx++) {
        for(size_t connectWordIdx = 0; connectWordIdx < connectWordLen; connectWordIdx++) {
            if(tryInsertWordOnIndex(
                word, 
                wordIdx, 
                connectWordNum, 
                connectWordIdx
            )) {
                return true;
            }
        }
    }

    return false;
}

void Crosswords::insertWord(WordInformation &wordInfo) {
    size_t wordLen = strlen(wordInfo.word);

    for (size_t i = 0; i < wordLen; i++) {
        Coordinate currentCoordinate = wordInfo.startCoord;

        if (wordInfo.orientation == Orientation::HORIZONTAL) {
            currentCoordinate.col += i;
        } else {
            currentCoordinate.row += i;
        }

        grid.grid[currentCoordinate.row][currentCoordinate.col] = wordInfo.word[i];
    }

    insertedWords[numWords] = wordInfo;
    strcpy(insertedWords[numWords].word, wordInfo.word);
    insertedWords[numWords].guessed = false;
    numWords++;
}

bool Crosswords::tryInsertWordOnIndex(
    char* word, 
    size_t wordIdx, 
    size_t connectWordNum,
    size_t connectWordIdx
) {
    WordInformation& connectWordInfo = insertedWords[connectWordNum];

    if (word[wordIdx] != connectWordInfo.word[connectWordIdx]) {
        return false;
    }

    //  the letters are the same

    WordInformation wordInfo;
    wordInfo.startCoord = getInsertStartCoord(word, wordIdx, connectWordInfo, connectWordIdx);
    if(!inBounds(wordInfo.startCoord)) {
        return false;
    }

    wordInfo.orientation = utils::flipOrientation(connectWordInfo.orientation);
    strcpy(wordInfo.word, word);


    if(canInsertWord(wordInfo, wordIdx)) {
        insertWord(wordInfo);
        return true;
    }
    return false;
}

bool Crosswords::inBounds(Coordinate &coord) {
    return coord.row >= 0 && coord.row < grid.rows && coord.col >= 0 && coord.col < grid.cols;
}

bool Crosswords::inBounds(WordInformation &wordInfo) {
    size_t wordLen = strlen(wordInfo.word);

    if (wordInfo.orientation == Orientation::HORIZONTAL) {
        return wordInfo.startCoord.row >= 1 && wordInfo.startCoord.row + 1 < grid.rows && wordInfo.startCoord.col >= 1 && wordInfo.startCoord.col + wordLen + 1 <= grid.cols;
    } else {
        return wordInfo.startCoord.row >= 1 && wordInfo.startCoord.row + wordLen + 1 <= grid.rows && wordInfo.startCoord.col >= 1 && wordInfo.startCoord.col < grid.cols + 1;
    }
}


bool Crosswords::canInsertWord(WordInformation &wordInfo, size_t intersectIdx) {

    if (!inBounds(wordInfo)) {
        return false;
    }

    Orientation orientation = wordInfo.orientation;

    if(orientation == Orientation::HORIZONTAL) {
        if (grid.grid[wordInfo.startCoord.row][wordInfo.startCoord.col - 1] != GRID_PLACEHOLDER ) {
            return false;
        }
    } else {
        if (grid.grid[wordInfo.startCoord.row - 1][wordInfo.startCoord.col] != GRID_PLACEHOLDER ) {
            return false;
        }
    }

    size_t wordLen = strlen(wordInfo.word);

    for(size_t i = 0; i < wordLen; i++) {

        if (i == intersectIdx) {
            continue;
        }

        Coordinate currentCoordinate = wordInfo.startCoord;
        Coordinate coordinatesToCheck[3];

        if(orientation == Orientation::HORIZONTAL) {
            currentCoordinate.col += i;
            for (size_t j = 0; j < 3; j++) {
                coordinatesToCheck[j] = currentCoordinate;
                coordinatesToCheck[j].row += j - 1;
            }
        } else {
            currentCoordinate.row += i;
            for (size_t j = 0; j < 3; j++) {
                coordinatesToCheck[j] = currentCoordinate;
                coordinatesToCheck[j].col += j - 1;
            }
        }

        for (size_t j = 0; j < 3; j++) {
            if (grid.grid[coordinatesToCheck[j].row][coordinatesToCheck[j].col] != GRID_PLACEHOLDER) {
                return false;
            }
        }
    }

    if(orientation == Orientation::HORIZONTAL) {
        if (grid.grid[wordInfo.startCoord.row][wordInfo.startCoord.col + wordLen] != GRID_PLACEHOLDER ) {
            return false;
        }
    } else {
        if (grid.grid[wordInfo.startCoord.row + wordLen][wordInfo.startCoord.col] != GRID_PLACEHOLDER ) {
            return false;
        }
    }

    return true;
}



Coordinate Crosswords::getInsertStartCoord(
    char *word,
    size_t wordIdx,
    WordInformation &connWordInfo,
    size_t connectWordIdx
) {

    // will modify to be correct
    Coordinate wordStart = connWordInfo.startCoord;

    switch (connWordInfo.orientation) {
        case Orientation::HORIZONTAL:
            wordStart.col += connectWordIdx;
            wordStart.row -= wordIdx;
            break;
        case Orientation::VERTICAL:
            wordStart.row += connectWordIdx;
            wordStart.col -= wordIdx;
    }

    return wordStart;
}


void Crosswords::insertFirstWord(char * word) {

    size_t wordLength = strlen(word);

    size_t startColumn = (grid.cols - wordLength) / 2;
    size_t startRow = grid.rows / 2; 
    

    // Store the word's information
    WordInformation wordInfo;

    wordInfo.startCoord = {startRow, startColumn};
    wordInfo.orientation = Orientation::HORIZONTAL;
    strcpy(wordInfo.word, word);

    insertWord(wordInfo);
}

