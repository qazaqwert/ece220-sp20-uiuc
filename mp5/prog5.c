// partners: Jerry Balan (agbalan2), Alice Getmanchuk (aliceg3), Jacob Tentis (jtentis2)
 
// This file provides 3 functions we implemented for main.c which helps the guessing game work.
// This file also provides other functions that we did not implement.
// The functions we implemented are set_seed which sets the random seed based off of user
// input. start_game which initializes the global variables to default and generates the correct
// sequence of star-wars 'personalities' to try and guess (and keep it hidden to user).
// make_guess takes a user's 4 guesses and splits the one input into 4 strings that it can
// compare to the generated string from start_game with.
 
/*
*
* prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
*           student code -- GOLD VERSION by Steven S. Lumetta
*/
 
 
/*
* The functions that you must write are defined in the header file.
* Blank function prototypes with explanatory headers are provided
* in this file to help you get started.
*/
 
 
 
#include <stdio.h>
#include <stdlib.h>
 
#include "prog5.h"
 
int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
* INPUT: none
* OUTPUT: none
*/
void print_pool() {
   printf("Valid term to guess:\n\t");
   for(int i = 0; i < 8 ; ++i) {
       printf("%s ", pool[i]);
   }
   printf("\n");
}
 
/*
* is_valid -- This function checks whether a string is valid
* INPUTS: str -- a string to be checked
* OUTPUTS: none
* RETURN VALUE: 0 if str is invalid, or 1 if str is valid
* SIDE EFFECTS: none
*/
int is_valid(char* str) {
   int i = 0;
   if (str == NULL) {
       return 0;
   }
   for (i = 0; i < 8; i++) {
       if (strcmp(str, pool[i]) == 0) {
           return 1;
       }
   }
   return 0;
}
 
 
/*
* set_seed -- This function sets the seed value for pseudorandom
* number generation based on the number the user types.
* The input entered by the user is already stored in the string seed_str by the code in main.c.
* This function should use the function sscanf to find the integer seed value from the
* string seed_str, then initialize the random number generator by calling srand with the integer
* seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
* INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
* OUTPUTS: none
* RETURN VALUE: 0 if the given string is invalid (string contains anything
*               other than a single integer), or 1 if string is valid (contains one integer)
* SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
*               if string is invalid. Prints nothing if it is valid.
*/
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
   int seed;
   char post[2];
   if (sscanf (seed_str, "%d%1s", &seed, post) != 1) { // Puts integer in seed, any other garbage in post.
     // your code here
       printf("set_seed: invalid seed\n"); // If there is garbage in post, print error and return 0.
       return 0;
   }
   srand(seed); // Set the random seed to the inputted value
   return 1;
   // your code here
 
}
 
 
/*
* start_game -- This function is called by main.c after set_seed but before the user makes guesses.
*               This function creates the four solution numbers using the approach
*               described in the wiki specification (using rand())
*               The four solution numbers should be stored in the static variables defined above.
*               The values at the pointers should also be set to the solution numbers.
*               The guess_number should be initialized to 1 (to indicate the first guess)
*               The score should be initialized to -1.
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
*/
void start_game () {
   //your code here
   int i;
   for(i = 0; i <=3; i++) { // Loop through the strings (array of chars)
       strcpy(solutions[i], pool[(rand() % 8)]); // Copy a random string from pool into each of the solution strings
   }
 
   guess_number = 1; // Set default guess number
   max_score = -1; // Set default max_score
 
}
 
/*
* make_guess -- This function is called by main.c after the user types in a guess.
*               The guess is stored in the string guess_str.
*               The function must calculate the number of perfect and misplaced matches
*               for a guess, given the solution recorded earlier by start_game
*               The guess must be valid (contain only 4 strings from pool). If it is valid
*               the number of correct and incorrect matches should be printed, using the following format
*               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
*               If valid, the guess_number should be incremented.
*               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
*               For an invalid guess, the guess_number is not incremented.
* INPUTS: guess_str -- a string consisting of the guess typed by the user
* OUTPUTS: none
* RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid,
*               or 0 if it is invalid
* SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
*               or an error message (invalid guess)
*               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
*/
int make_guess (const char guess_str[]) {
 // Define variables
   int score = 0;
   int i, j;
   int perf = 0;
   int imperf = 0;
   int match_sol[4] = {0,0,0,0};
   int match_guess[4] = {0,0,0,0};
   char overflow_str[2]; // Overflow for extra garbage
   char guess[4][10]; // Array of 4 strings (each string is an array of 10 chars)
 
   // Split up guess_str, which is one big string with 4 guesses into the individual guesses
   if(sscanf(guess_str, "%s%s%s%s%1s", guess[0], guess[1], guess[2], guess [3], overflow_str) != 4) {
       printf("make_guess: invalid guess\n"); // If there is not exactly 4 guesses, there is an error
       return 0;
   }
  
   // Check each user guess and see if it is valid using the provided function
   for(i = 0; i < 4; i++) { // Iterate through each guess
       if(is_valid(guess[i]) == 0) {
           printf("make_guess: invalid guess\n"); // If the 4 guesses are not ALL valid, there is an error
           return 0; // Return 0 if error
       }
   }
 
   // Iterate through all of the guesses/solutions and check if any perfect match
   for(i = 0; i < 4; i++){
       if(strcmp(guess[i], solutions[i]) == 0) { // Checks if guess is in the same place & same string as solution
           score += 1000; // Update score
           perf++; // Update perfect matches counter
           match_sol[i] = 1; // Mark where the perfect match locations are in the array
           match_guess[i] = 1; // Mark where the perfect match locations are in the array
       }
   }
 
   // Iterate through all of the guesses & solutions and check if any imperfect match
   for(i = 0; i < 4; i++) { // Iterate through guesses
       if(match_guess[i] == 1) { // If this guess has been matched with a solution, skip comparison
           continue;
       }
       for(j = 0; j < 4; j++) { // Iterate through solutions
           if(match_sol[j] == 1) { // If this solution has been matched with a guess, skip comparison
           continue;
           }
           if(strcmp(guess[i], solutions[j]) == 0) { // Checks if guess and solutoins contain the same string
               match_sol[j] = 1; // Mark the solution corresponding to the imperfectly matched guess
               match_guess[i] = 1; // Mark the guess corresponding to the imperfectly matched solution
               imperf++; // Update imperfect solution counter
               score += 100; // Update score
           }
 
 
       }
   }
 
   // Update max_score if score is larger
   if (score > max_score) {
       max_score = score;
   }
 
   // Print result from guess
   printf("With guess %d, you got %d perfect matches and %d misplaced matches.\nYour score is %d and current max score is %d.\n",
   guess_number, perf, imperf, score, max_score);
 
   if(perf == 4) { // If 4 of 4 guesses are perfectly correct, return 2
       return 2;
   }
   return 1; // Otherwise, with no errors, return 1
}
 
 
 
 
 
 

