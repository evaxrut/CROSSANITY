#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "include/scoreboard.hpp"
#include "include/crossword.hpp"
#include "include/constants.hpp"
#include "include/utils.hpp"


const char *HEADER = R"(
╔═════════════════════════════════════════════════════════════════╗    
║    ___  ____   __   ____  ____   __   __ _  __  ____  _  _  _   ║   
║   / __)(  _ \ /  \ / ___)/ ___) / _\ (  ( \(  )(_  _)( \/ )/ \  ║ 
║  ( (__  )   /(  O )\___ \\___ \/    \/    / )(   )(   )  / \_/  ║  
║   \___)(__\_) \__/ (____/(____/\_/\_/\_)__)(__) (__) (__/  (_)  ║  
║                                                                 ║
╚═════════════════════════════════════════════════════════════════╝
)";

const char *DIRECTIONS = "(k) up   (j) down   (h) left    (l) right    (g) guess   (v) hint";


char getCharInput() {
    char userInput;
    std::cin >> userInput;
    tolower(userInput);
    return userInput;
}


void scoreboard(){
    while(true) {
        utils::clearScreen();
        std::cout << HEADER << std::endl;
        std::cout << "\nSCOREBOARD MENU \n(W) For whole scoreboard \n(T) For top five" << std::endl;
        // TODO: make a get input function
        char userInput = getCharInput();

        

        // while true pattern
        //TODO: switch case
        bool valid = false;
        if (userInput == 'w'){
            getScoreboard(-1);
            valid = true;
        }
        else if (userInput == 't'){
            getScoreboard(5);
            valid = true;
        }

        if (valid) {
            std::cout << "\nPress enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        std::cout << "You did not choose correctly. Try again." << std::endl;
    }
}

int main() {
    srand(time(NULL));


    while (true) {
        utils::clearScreen();
        std::cout << HEADER << std::endl;
        std::cout << "\nChoose stuff \n"
            << "(C) To play crossword \n"
            << "(S) To see scoreboard \n" 
            << "(Q) To exit" 
            << std::endl;

        char userInput = getCharInput();
   
        if (userInput == 'c') {
            playCrossword();
        }
        else if (userInput == 's') {
            scoreboard();
        }
        else if(userInput == 'q') {
            break;
        }
        else {
            std::cout << "You did not choose correctly. Try again." << std::endl;
        }
    }


}
