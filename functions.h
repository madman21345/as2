#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// Function prototypes
void display( const char *randomWord, char guessedLetters[], char displayWord[] );
char oldInputGuess();
char inputGuess(char guessedLetters[]);

bool playWordGuessingGame( const char * randomWord );


char autoguess( int numPossibleWords, char ** possibleWords, char *displayWord, char *guessedLetters );

bool playWordGuessingGameAutomatic ( const char * randomWord, char ** words, int numWords, int numSuggestion );


#endif
