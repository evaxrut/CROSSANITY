#include "../include/utils.hpp"
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>

namespace utils {
    int getRandomNumber(int low, int high) {
        return  rand() % (high - low + 1) + low;
    }

    Orientation flipOrientation(Orientation orientation) {
        if (orientation == Orientation::HORIZONTAL) {
            return Orientation::VERTICAL;
        } else {
            return Orientation::HORIZONTAL;
        }
    }

    char getChar() {
        struct termios oldt, newt; // Termios structs to hold the terminal settings
        char ch;

        // Get the current terminal settings (to restore them later)
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt; // Copy the settings to modify them

        // Turn off canonical mode (buffered i/o) and local echo
        newt.c_lflag &= ~(ICANON | ECHO);

        // Apply the new settings to the terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // Read a single character
        ch = getchar();

        // Restore the old terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch; // Return the character we got
    }

    void clearScreen() {
        system("clear");
    }

    void scrambleWord(char *word) {
    int length = strlen(word);
    for (int i = length - 1; i > 0; i--) {
        int newSpot = rand() % (i);
        char temp = word[i];
        word[i] = word[newSpot];
        word[newSpot] = temp;
    }
}
}