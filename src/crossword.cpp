#include <iostream>
#include <string.h>
#include <time.h>
#include "../include/constants.hpp"
#include "../include/crossword.hpp"
#include "../include/Crosswords.hpp"
#include "../include/grid.hpp"
#include "../include/utils.hpp"
#include "../include/types.hpp"
#include "../include/CrosswordGame.hpp"
#include "../include/scoreboard.hpp"

int calculateScore(double timeUsed, size_t hintsUsed, size_t wordsGuessed){
    int score = wordsGuessed * 10 - hintsUsed;
    if ((timeUsed / 60.0) < TIME_BONUS_LIMIT_MINUTES){
        score *= 2;
    }

    return score;
}

void playCrossword(){
    CrosswordGame game{};

    time_t startTime = time(NULL);
    game.play();
    time_t endTime = time(NULL);

    double timeUsed = difftime(endTime, startTime);
    size_t hintsUsed = game.hintsUsed;
    size_t wordsGuessed = game.wordsGuessed;

    int score = calculateScore(timeUsed, hintsUsed, wordsGuessed);

    addToScoreboard(score);
}

