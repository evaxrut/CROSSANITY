#pragma once

#include "Crosswords.hpp"


enum CoordinateViewState {
    GUESSED,
    HOVERED_1,
    HOVERED_2,
    HIDDEN,
    NO_WORD,
};

class CrosswordGame {

private:
    Crosswords crosswords;
    Coordinate cursor;

    void printScores();
    void browse();
    bool hint();
    void moveCursor(char input);
    void printGrid(WordInformation ** hoverWords, size_t numHovered);
    void printWords(WordInformation ** words, size_t numWords);
    void tryGuess(WordInformation ** words, size_t numWords);
    size_t chooseWord(WordInformation ** words, size_t numWords);
    CoordinateViewState getCoordinateState(
        Coordinate &coord, 
        WordInformation ** hoverWords, 
        size_t numHoverWords
    );

public:
    CrosswordGame();
    ~CrosswordGame();

    size_t hintsUsed;
    size_t wordsGuessed;

    void play();
};