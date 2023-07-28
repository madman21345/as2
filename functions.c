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
    printf("\n%s\n\n", displayWord);
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

        if(result != 1 || !( (guess >= 'a' && guess <= 'z') ) ) {
            // Clearing the input buffer outside now to get rid of multiple characters
            printf("Invalid input(try lowercase). Enter again: ");
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

    char *guessedLetters = malloc(MAX_LETTERS * sizeof(char));
    char guess;
    int totalGuesses = 0;
    int attempts = 0;
    char *displayedWord = malloc(strlen(randomWord) * sizeof(char)); //use this to store the word with '-' where not guessed yet.

    if(displayedWord == NULL || guessedLetters == NULL) {
        printf("MEMORY ALLOCATION FAILED");return 0;
    }

    //< some of your code if necessary >
    //display blank word so that there's some insight from how big word is
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
                if(attempts < MAX_ATTEMPTS -1) {printf("Incorrect Guess. Try again.\n");}
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
    //free(guessedLetters);
    //free(displayedWord);
    
    return false;
}

//asked chatgpt for help with removing elements from allocated arrays, took parts of it. was extremely confusing
void removeElement(char **array, int index, int* size) {
    if (index < 0 || index >= *size) {
        // Invalid index, do nothing.
        return;
    }

    // Shift the remaining elements to fill the gap.
    for (int i = index; i < *size; i++) {
        array[i] = array[i + 1];
    }

    // Free the memory no longer occupied.
    free(array[*size]);
    // Decrement the size of the array.
    (*size)--;

    // Resize the array to free up the memory of the last element (which is now a duplicate).
    //*array = realloc(array, (*size) * sizeof(char*));
}

char autoguess( char *guessedLetters ) {
    char guess;
    //according to the concise oxford dictionary these are the most common letters in order
    char *alpha = "eariotnslcudpmhgbfywkvxzjq";

    //choose a letter to guess
    for(int i = 0; i < MAX_LETTERS; i++ ) {
        if(strchr(guessedLetters, alpha[i]) == NULL) {
            guess = alpha[i];
            printf("%c", guess);
            break;
        }
    }
    
    return guess;
}

void removeGuessed(int *numPossibleWords, char ** possibleWords, char *displayWord, char *guessedLetters ) {
    char uGuessedLetters[MAX_LETTERS];
    int nums = 0;
    //get all of the unused letters
    for(int i = 0; i < MAX_LETTERS; i++) {
        if(strchr(displayWord,guessedLetters[i]) == NULL) {
            uGuessedLetters[nums++] = guessedLetters[i];
        }
    }
    //remove words that have the guessedletters that arent correct since they arent in it
    if(nums > 0) {
        int i = 0;
        while(i < *numPossibleWords) {
            bool removal = false;
            for(int j = 0; j < nums; j++) {

                if(strchr(possibleWords[i],uGuessedLetters[j])) {
                    removal = true;//removeElement(possibleWords,i,numPossibleWords);
                    break;
                }
            }
            if(removal) {
                removeElement(possibleWords,i,numPossibleWords);
            } else {
                i++;
            }
        }
    }

    //go through possible words and remove any that it cant be
    int i = 0;
    while( i < *numPossibleWords) {
        bool removal = false;

        for (size_t j = 0; j < strlen(displayWord); j++) {

            if(displayWord[j] == '-' || possibleWords[i][j] == displayWord[j]) {
                continue;
            } else {
                //remove words that aren't possible anymore
                removal = true;
                break;
            }
        }
        if(removal) {
            removeElement(possibleWords,i,numPossibleWords);
        } else{
            i++;
        }
    }
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
    char ** possibleWords = malloc(numWords * sizeof(char *));
    int numPossibleWords = 0;

    char *guessedLetters = malloc(MAX_LETTERS * sizeof(char));
    char guess;
    int totalGuesses = 0;
    int attempts = 0;
    char *displayedWord = malloc(strlen(randomWord) * sizeof(char)); //use this to store the word with '-' where not guessed yet.

    if(displayedWord == NULL || guessedLetters == NULL || possibleWords == NULL) {
        printf("MEMORY ALLOCATION FAILED");return 0;
    }

    //initializing possibleWords using length of words
    for(int i = 0; i < numWords; i++) {
        if(strlen(words[i]) == strlen(randomWord)) {
            possibleWords[numPossibleWords] = malloc((strlen(words[i]) + 1) * sizeof(char));
            strcpy(possibleWords[numPossibleWords++], words[i]);
        }
    }
    possibleWords[numPossibleWords] = NULL;
    //free the rest
    //for (int i = numPossibleWords+1; i < numWords; i++) {
    //    free(possibleWords[i]);
    //}

    //display blank word so that there's some insight from how big word is
    printf("\nContinue entering letters until you complete the word.\n");
    printf("Your word is %ld letters long,\n", strlen(randomWord));
    display(randomWord, guessedLetters, displayedWord);

    bool print = true;//i didnt wanna figure this out. so work around to only print once
    while ( attempts < MAX_ATTEMPTS ) {
        while(true) {
            printf("Please wait. Eliminating words...\n");
            removeGuessed(&numPossibleWords, possibleWords, displayedWord, guessedLetters); //ideally only need to do this when fail, and only need to pass the failed character, but I dont have more time.
            if(attempts < MAX_ATTEMPTS -1) {
                if(numPossibleWords > 1) {
                    printf("Attempt %d: ", attempts+1);
                    //guess = autoguess( guessedLetters );
                    guess = inputGuess( guessedLetters );
                } else {
                    printf("ONLY 1 WORD REMAINS");
                    attempts = 3;
                    ;//in the example when there was only 1 word left it just kept putting the same letter
                }
            } else {
                int nums = numSuggestion;
                if(numPossibleWords < numSuggestion) {nums = numPossibleWords;}
                if(print) {
                    printf("\nThere are only %d words left.\nHere is %d(up to %d) possible words: \n", numPossibleWords, nums, numSuggestion);
                    for(int i=0; i<nums; i++) {
                        if(possibleWords[i] == NULL) {break;}
                        printf("%s\n",possibleWords[i]);
                    }
                    print = false;
                }
                printf("Attempt %d: ", attempts+1);
                guess = inputGuess(guessedLetters);
                //guess = oldInputGuess();
            }

            if (strchr(guessedLetters, guess) == NULL) {
                guessedLetters[totalGuesses++] = guess;
            }

            display(randomWord, guessedLetters, displayedWord); //display progress

            //go next attempt if not correct guess
            if(strchr(randomWord, guess)== NULL) {
                if(attempts < MAX_ATTEMPTS -1) {printf("Incorrect Guess. Try again.\n");}
                break;
            }
            // and end if guessed all letters
            if(strcmp(randomWord, displayedWord) == 0) {
                return true;
            }
        }
        

        attempts++;
    }
    free(guessedLetters);
    for(int i = 0; i < numPossibleWords; i++) {
        free(possibleWords[i]);
    }
    free(possibleWords);
    free(displayedWord);
    
    return false;
}



//used lecture notes and main.c to understand how malloc works, but also used chatgpt for clarification on
//how it works and how to use it and free it.
