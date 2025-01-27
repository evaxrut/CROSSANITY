#include <iostream>
#include <string.h>
#include <unistd.h>
#include "../include/CrosswordGame.hpp"
#include "../include/constants.hpp"
#include "../include/colors.hpp"
#include "../include/utils.hpp"

#define UP 'k'
#define DOWN 'j'
#define LEFT 'h'
#define RIGHT 'l'
#define GUESS 'g'
#define HINT 'v'


CrosswordGame::CrosswordGame(): hintsUsed(0), wordsGuessed(0) {}

CrosswordGame::~CrosswordGame() {}

CoordinateViewState CrosswordGame::getCoordinateState(
    Coordinate &coord, 
    WordInformation ** hoverWords, 
    size_t numHoverWords
) {

    WordInformation *wordsAtCoordinate[2];
    size_t numWordsAtCoordinate = crosswords.wordsOnCoordinate(coord, wordsAtCoordinate, true);


    bool word = false;
    for (size_t i = 0; i < numWordsAtCoordinate; i++) {
        word = true;
        if (wordsAtCoordinate[i]->guessed) {
            return GUESSED;
        }
    } 

    bool hovered1 = false;
    bool hovered2 = false;
    for (size_t i = 0; i < numHoverWords; i++) {
        if (crosswords.wordIsOnCoordinate(coord, hoverWords[i])) {
            if (i == 0){
                hovered1 = true;
            }
            if (i == 1) {
                hovered2 = true;
            }
        }
    }

    if (hovered1) {
        return HOVERED_1;
    }

    if (hovered2) {
        return HOVERED_2;
    }

    if (word) {
        return HIDDEN;
    }
    
    return NO_WORD;
}


void CrosswordGame::printScores() {
    std::cout << "Words guessed: " << wordsGuessed 
              << "/" 
              << crosswords.numWords 
              << "\nHints used: "
              << hintsUsed
              << std::endl;

    std::cout << "If you win in under " << TIME_BONUS_LIMIT_MINUTES 
              << " minutes, your score will be " 
              << color::GREEN_FOREGROUND_START 
              << "DOUBLED!"  << color::COLOR_END << std::endl;
}


void CrosswordGame::printGrid(WordInformation ** howerWords, size_t numHovered){

    std::cout << HEADER << DIRECTIONS << std::endl;
    printScores();

    Grid &grid = crosswords.grid;

    for (size_t i = 0; i < GRID_HEIGHT; i++) {
        for (size_t j = 0; j < GRID_WIDTH; j++) {

            Coordinate coord = {i, j};

            CoordinateViewState state = getCoordinateState(coord, howerWords, numHovered);

            switch(state) {
                case GUESSED:
                    std::cout << color::GREEN_FOREGROUND_START;
                    break;
                case HOVERED_1:
                    std::cout << color::MAGENTA_FOREGROUND_START;
                    break;
                case HOVERED_2:
                    std::cout << color::CYAN_FOREGROUND_START;
                    break;
                case HIDDEN:
                    std::cout << color::WHITE_FOREGROUND_START;
                    break;
                case NO_WORD:
                    break;
            }

            if (grid.hinted[i][j] && state != GUESSED && state != HOVERED_1 && state != HOVERED_2) {
                std::cout << color::YELLOW_FOREGROUND_START;
            }

            if (cursor.row == i && cursor.col == j) {
                std::cout << color::CYAN_BACKGROUND_START;
            }

            char symbol = ' ';

            if (state == GUESSED || crosswords.grid.hinted[i][j]) {
                symbol = crosswords.grid.grid[i][j];
            } else if (state == HIDDEN || state == HOVERED_1 || state == HOVERED_2) {
                symbol = '#';
            }

            std::cout << symbol << color::COLOR_END << " ";
        }
        std::cout << std::endl;
    }
}

void CrosswordGame::printWords(WordInformation ** words, size_t numWords) {
    for (size_t i = 0; i < numWords; i++) {
        if (i == 0){
            std::cout << color::MAGENTA_FOREGROUND_START;
        } else {
            std::cout << color::CYAN_FOREGROUND_START;
        }
        std::cout  << words[i]->scrambled 
                   << color::COLOR_END 
                   << std::endl;
    }
    std::cout << std::endl;
}

void CrosswordGame::browse() {

    WordInformation *hoverWords[2];
    size_t numHovered = 0;

    while (true) {
        numHovered = crosswords.wordsOnCoordinate(cursor, hoverWords, false);

        utils::clearScreen();
        printGrid(hoverWords, numHovered);
        printWords(hoverWords, numHovered);

        char c = utils::getChar();
        if (c == GUESS) {
            tryGuess(hoverWords, numHovered);
            if(wordsGuessed == crosswords.numWords) {
                std::cout << color::GREEN_FOREGROUND_START
                          << "Congratulations! You have guessed all the words!"
                          << color::COLOR_END
                          << std::endl;
                sleep(2);
                break;
            }
        }
        if(c == HINT) {
            hint();
        }
        moveCursor(c);
    }
}

bool CrosswordGame::hint() {
    if(crosswords.grid.hinted[cursor.row][cursor.col]) {
        std::cout << color::RED_BACKGROUND_START
                  << color::WHITE_FOREGROUND_START
                  << "This cell already revealed"
                  << color::COLOR_END
                  << std::endl;

        sleep(2);
        return false;
    }

    WordInformation *words[2];
    size_t numWordsFound = crosswords.wordsOnCoordinate(cursor, words, true);

    bool foundGuessed = false;
    bool foundUnguessed = false;

    for (size_t i = 0; i < numWordsFound; i++) {
        if (words[i]->guessed) {
            foundGuessed = true;
        } else {
            foundUnguessed = true;
        }
    }

    if(!foundGuessed && foundUnguessed) {
        crosswords.grid.hinted[cursor.row][cursor.col] = true;
        hintsUsed++;
        return true;
    }

    std::cout << color::RED_BACKGROUND_START
                << color::WHITE_FOREGROUND_START
                << "Not over hidden character!"
                << color::COLOR_END
                << std::endl;

    sleep(2);
    return false;
}

void CrosswordGame::tryGuess(WordInformation ** words, size_t numWords) {
    if (numWords == 0) {
        std::cout << color::RED_BACKGROUND_START
                  << color::WHITE_FOREGROUND_START
                  << "No word hovered"
                  << color::COLOR_END
                  << std::endl;

        sleep(2);
        return;
    }

    size_t guessIdx;
    if(numWords == 1) {
        guessIdx = 0;
    } else {
        guessIdx = chooseWord(words, numWords);
    }

    char guess[1000];
    std::cout << "Enter your guess: ";
    std::cin >> guess;

    if (strcmp(guess, words[guessIdx]->word) == 0) {
        std::cout << color::GREEN_FOREGROUND_START << "Correct!" << color::COLOR_END << std::endl;
        words[guessIdx]->guessed = true;
        wordsGuessed++;
        sleep(1);
    } else {
        std::cout << color::RED_FOREGROUND_START << "Incorrect!" << color::COLOR_END << std::endl;
        sleep(2);
    }

}


size_t CrosswordGame::chooseWord(WordInformation ** words, size_t numWords) {

    size_t currentIdx = 0;

    while (true) {
        utils::clearScreen();
        printGrid(words, numWords);
        for(size_t i = 0; i < numWords; i++) {
            if (i == currentIdx) {
                std::cout << "❯ ";
            }

            if (i == 0){
                std::cout << color::MAGENTA_FOREGROUND_START;
            } else {
                std::cout << color::CYAN_FOREGROUND_START;
            }

            std::cout << words[i]->scrambled
                      << color::COLOR_END
                      << std::endl;
        }
        std::cout << "\n" << "(" << GUESS << " to choose)" << std::endl;

        char c = utils::getChar();

        switch (c) {
            case UP:
                if (currentIdx > 0) {
                    currentIdx--;
                }
                break;
            case DOWN:
                if (currentIdx < numWords - 1) {
                    currentIdx++;
                }
                break;
            case GUESS:
                return currentIdx;
        }
    }
}

void CrosswordGame::play() {
    cursor = {0, 0};
    browse();
}

void CrosswordGame::moveCursor(char input) {
    switch (input) {
        case UP:
            if (cursor.row > 0) {
                cursor.row--;
            }
            break;
        case DOWN:
            if (cursor.row < GRID_HEIGHT - 1) {
                cursor.row++;
            }
            break;
        case LEFT:
            if (cursor.col > 0) {
                cursor.col--;
            }
            break;
        case RIGHT:
            if (cursor.col < GRID_WIDTH - 1) {
                cursor.col++;
            }
            break;
        default:
            break;
    }
}