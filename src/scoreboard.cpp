#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "constants.hpp"
#include <unistd.h>



void printScoreboard(const char names[][30], const int scores[], int numEntries, int amount){
    std::cout << "\nWHOLE SCOREBOARD! " << std::endl;

    if (amount == 5){
        numEntries = 5;
    }

    for (int i = 0; i < numEntries; i++) {
        std::cout << names[i] << ": " << scores[i] << std::endl;
    }
}

void swapScores(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapNames(char *name1, char *name2) {
    char tempName[strlen(name1)]; 

    strcpy(tempName, name1);
    strcpy(name1, name2);
    strcpy(name2, tempName);
}

void sort(int scores[], char names[][30], int numEntries) {
    for (int i = 0; i < numEntries - 1; i++) {
        for (int j = 0; j < numEntries - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                swapScores(scores[j], scores[j + 1]);
                swapNames(names[j], names[j + 1]);
            }
        }
    }
}

void getScoreboard(int amount) {
    std::ifstream file(OUTPUT_FILE_NAME);
    char names[MAX_PLAYERS][30];
    int scores[MAX_PLAYERS];
    int numEntries = 0;

    while (file >> names[numEntries] >> scores[numEntries]) {
        numEntries++;
    }

    sort(scores, names, numEntries);

    printScoreboard(names, scores, numEntries, amount);

    file.close();
}

void addToScoreboard(int score){
    char name[100];
    std::cout << "We are adding you to the scoreboard! \nInsert first name: ";
    std::cin >> name;


    std::ofstream file(OUTPUT_FILE_NAME, std::ios::app);
    file << "\n" << name << " " << score;

    std::cout << "You have been added to the scoreboard :p " << std::endl;
    file.close();
    sleep(2);
}