#pragma once

#include "types.hpp"

namespace utils {

    int getRandomNumber(int low, int high);

    Orientation flipOrientation(Orientation orientation);

    char getChar();

    void clearScreen();

    void scrambleWord(char *word);
}

