#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "functions.h"

#define MAX_LETTERS 26

//didn't define in functions.h since its only used locally here
//displays the current situation of the word
void display( const char *randomWord, char guessedLetters ) {

}

//main program for part A
bool playWordGuessingGame ( const char * randomWord ) {
    char guessedLetters[MAX_LETTERS];
    char guess;
    char totalGuesses = 0;
    int attempts = 0;
    //< some of your code if necessary >
    //display blank word so that there's some insight of how big word is


    while ( attempts < MAX_ATTEMPTS ) {
        //while(1) 
        scanf(" %c", &guess);
        guessedLetters[totalGuesses++] = guess;
        //< here use scanf (" %c", & guess ) to recieve input from user >
        //< you can use strcmp function to compare two string ! >
        //<if all letters were guessed here use return true ; >

        attempts++;
    }
    //<if the run reaches here it means after MAX_ATTEMPTS ... >
    //< the letters are not found , so use return false ; >
    return false;
}