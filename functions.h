#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// Function prototypes

bool playWordGuessingGame( const char * randomWord );
void display( const char *randomWord, char guessedLetters[], char displayWord[] );
char oldInputGuess();
char inputGuess(char guessedLetters[]);


#endif
