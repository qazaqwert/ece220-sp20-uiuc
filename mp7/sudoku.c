// partners: Jerry Balan (agbalan2), Alice Getmanchuk (aliceg3), Jacob Tentis (jtentis2)
// MP7 - Sudoku Solver
// In this MP, we created a program to solve a Sudoku puzzle.
//Our program checks to see if the sudoku is full.
//If not, it finds the first empty value and then loops through the possible values (1-9)
//to see if they fit in the puzzle correctly, and then checks to see if the correct value
//obtained solves the puzzle as a whole.
//It uses recursion to loop through all the empty spaces.
//In the end, the initial puzzle and final/solved puzzle are printed.

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// 1 = true, 0 = false


// Function Declarations for the helper functions
int is_full(const int sudoku[9][9]);
int find_zero(const int sudoku[9][9], int *x, int *y);

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j;
  for(j = 0; j < 9; j++) {
    if(sudoku[i][j] == val) { // Checks if any variable in the row i is val
      return 1; // If so, return 1
    }
  }
  return 0; // Return 0 if val is not in row
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;
  for(i = 0; i < 9; i++) {
    if(sudoku[i][j] == val) { // Checks if any variable in the col j is val
      return 1; // If so, return 1
    }
  }
  return 0; // Return 0 if val is not in col
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  int x = i/3*3; // this finds the left-most index of each square by truncation with division
  int y = j/3*3; // this finds the upper-most index of each square by truncation with division
  int a, b;
  for(a = x; a < x + 3; a++) { // loops over all of the rows in the 3x3 square
    for(b = y; b < y + 3; b++) { // loops over all of the cols in the 3x3 square
      if(sudoku[a][b] == val) { // Checks of val is in each element of the 3x3 square
        return 1;
      }
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  //vibe checks the variables
  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_row(val, i, sudoku) == 0) &&
     (is_val_in_col(val, j, sudoku) == 0) &&
     (is_val_in_3x3_zone(val, i, j, sudoku) == 0)) {
    return 1;
  }
  return 0;
  // END TODO
}
// Function: is_full, checks if the sudoku grid has any empty spaces
// Returns 1 if full, 0 if empty
int is_full(const int sudoku[9][9]) {
  int i, j;

  for(i = 0; i < 9; i++) { //for each row and column
    for(j = 0; j < 9; j++) {
      if(sudoku[i][j] == 0) { //return 0 if there is an unfilled slot
        return 0;
      }
    }
  }
  return 1; //return 1 if board is all full
}

// Function: finds the next empty space in sudoku grid and changes the x, y to the row, col
// Returns 0 always
int find_zero(const int sudoku[9][9], int *x, int *y) {
  int i, j;
  for(i = 0; i < 9; i++) { // Loop through all of the rows in the sudoku grid
    for(j = 0; j < 9; j++) { // Loop through all of the cols in the sudoku grid
      if(sudoku[i][j] == 0) { // If a 0 is found...
        *x = i; // Set the parsed x to the row index of the 0 that is found
        *y = j; // Set the parsed y to the col index of the 0 that is found
        return 0; // Return to stop looking for next 0 as one is already found
      }
    }
  }
  return 0; // Edge case return
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i = 0; //initialize i and j
  int j = 0;

  if(is_full(sudoku) == 1) { //checks to see if there are any empty spaces, if not terminates
    return 1;
  } else {
    find_zero(sudoku, &i, &j); //if empty spots, places the location of next empty space in to i and j
  }

  int n; //initialize n

  for(n = 1; n <= 9; n++) { //checking to see if n (looping through 1-9) fits into the box correctly
    if(is_val_valid(n, i, j, sudoku) == 1) {
      sudoku[i][j] = n;
      if(solve_sudoku(sudoku) == 1) { //if the solved cell solves the whole puzzle, then terminate
        return 1;
      }
      sudoku[i][j] = 0; //place zero
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) { //loop through each row
    for(j=0; j<9; j++) { //loop through each column
      printf("%2d", sudoku[i][j]); //print int
    }
    printf("\n"); //after each int in row printed, new line
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r"); //open file
  assert(reader != NULL); //make sure file valid
  int i, j;
  for(i=0; i<9; i++) { //for each row and column, to find next int on board and store location into i and j
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader); //close file
}




