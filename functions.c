#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "functions.h"

#define MAX_LETTERS 26

//displays the current situation of the word
//also creates and store the word
void display( const char *randomWord, char guessedLetters[], char displayWord[] ) {
    for(size_t i=0; i<strlen(randomWord);i++) {
        //using the same idea from the input but this time with the corresponding index
        if (strchr(guessedLetters, randomWord[i]) != NULL) {
            displayWord[i] = randomWord[i];
        } else {
            displayWord[i] = '-';
        }
    }
    //null-terminating
    displayWord[strlen(randomWord)] = '\0';
    printf("%s\n\n", displayWord);
}

//from as1 just reused for char and modified for this use case
//not sure which I should use because in the example you can enter the same character multiple times, which doesnt really make sense to me
//eh nvm. ill use both so that I can input same letter when there is only 1 word left like the example to make it easier for me
char oldInputGuess() {
    char guess;
    while (true) {
        int result = scanf("%c", &guess);
        // Clear the input buffer
        while (getchar() != '\n');

        if(result != 1) {
            printf("Invalid input. Enter again: ");
            continue;
        }
    }
    return guess;
}
//from as1 just reused for char and modified for this use case
char inputGuess(char guessedLetters[]) {
    char guess;
    while (true) {
        int result = scanf(" %c", &guess);
        while (getchar() != '\n');

        if(result != 1) {
            // Clearing the input buffer outside now to get rid of multiple characters
            printf("Invalid input. Enter again: ");
            continue;
        }
        //asked chatgpt if there were any functions that could shorten my for loop I was using before
        //to loop through the entire array and check each value individually
        //it said strchr searches through the list and returns a pointer to the first match or NULL if no match
        //both ways work, this is just shorter, and newer to me.
        if (strchr(guessedLetters, guess) != NULL) {
            printf("You already guessed '%c'. Enter again: ", guess);
        } else {
            break;
        }
    }
    return guess;
}

//main program for part A
bool playWordGuessingGame ( const char * randomWord ) {
    char guessedLetters[MAX_LETTERS];
    char guess;
    int totalGuesses = 0;
    int attempts = 0;
    char displayedWord[strlen(randomWord)]; //use this to store the word with '-' where not guessed yet.

    //< some of your code if necessary >
    //display blank word so that there's some insight of how big word is
    printf("\nContinue entering letters until you complete the word.\n");
    printf("Your word is %ld letters long,\n", strlen(randomWord));
    display(randomWord, guessedLetters, displayedWord);

    while ( attempts < MAX_ATTEMPTS ) {
        while(true) {
            printf("Attempt %d: ",attempts+1);
            guess = inputGuess(guessedLetters);
            //guess = oldInputGuess();

            //added this so that can swap between the different input methods if the other one is wanted
            if (strchr(guessedLetters, guess) == NULL) {
                guessedLetters[totalGuesses++] = guess;
            }

            display(randomWord, guessedLetters, displayedWord); //display progress

            //go next attempt if not correct guess
            if(strchr(randomWord, guess)== NULL) {
                printf("Incorrect Guess. Try again.\n");
                break;
            }
            // and end if guessed all letters
            if(strcmp(randomWord, displayedWord) == 0) {
                return true;
            }
        }
        //< here use scanf (" %c", & guess ) to recieve input from user >
        //< you can use strcmp function to compare two string ! >
        //<if all letters were guessed here use return true ; >
        

        attempts++;
    }
    //<if the run reaches here it means after MAX_ATTEMPTS ... >
    //< the letters are not found , so use return false ; >
    return false;
}


// numSuggestion : is the maximum number of possible word that can be printed
// I have set this to 50 to make sure the Terminal is not gonna be messy
// numWords : is the number of words in words array
// words is the array of strings
// with each row one word and the columns are each string length
//main program for Part B
bool playWordGuessingGameAutomatic ( const char * randomWord, char ** words, int numWords, int numSuggestion )
{
    //< the same algorithm in Part A >
    //< until : attempts == MAX_ATTEMPTS - 1 >
    //< your code goes here >

    char guessedLetters[MAX_LETTERS];
    char guess;
    int totalGuesses = 0;
    int attempts = 0;
    char displayedWord[strlen(randomWord)]; //use this to store the word with '-' where not guessed yet.

    //display blank word so that there's some insight of how big word is
    printf("\nContinue entering letters until you complete the word.\n");
    printf("Your word is %ld letters long,\n", strlen(randomWord));
    display(randomWord, guessedLetters, displayedWord);

    while ( attempts < MAX_ATTEMPTS - 1 ) {
        while(true) {
            printf("Attempt %d: ",attempts+1);
            guess = autoguess(randomWord, words, numWords);
            //guess = inputGuess(guessedLetters);
            //guess = oldInputGuess();

            //added this so that can swap between the different input methods if the other one is wanted
            if (strchr(guessedLetters, guess) == NULL) {
                guessedLetters[totalGuesses++] = guess;
            }

            display(randomWord, guessedLetters, displayedWord); //display progress

            //go next attempt if not correct guess
            if(strchr(randomWord, guess)== NULL) {
                printf("Incorrect Guess. Try again.\n");
                break;
            }
            // and end if guessed all letters
            if(strcmp(randomWord, displayedWord) == 0) {
                return true;
            }
        }
        

        attempts++;
    }
    return false;
}

char autoguess(const char * randomWord, char ** words, int numWords) {
    
}
