#include "game.h"
// Alice Getmanchuk(aliceg3), Jerry Balan (agbalan2), Jacob Tentis (jtentis2)
//The goal of MP8 is to implement a game called 2048 which consists of a grid with tiles that have various values of 2^n. In this game you can combine tiles in the grid that share the same value to create a new tile consisting of their sum.
//You shift all of the tiles along the cardinal axes using the w,a,s,d keys (up, left, down, right). The goal is to combine enough tiles in order to obtain the 2048 tile.
//The objective of this MP was to write code for the indicated functions such as moving the pieces all directions, checking if there are legal moves, and more.
//
 
 
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
   and columns, initializing elements to -1 and return a pointer
   to it. (See game.h for the specification for the game data structure)
   The needed memory should be dynamically allocated with the malloc family
   of functions.
*/
{
   //Dynamically allocate memory for game and cells (DO NOT modify this)
   game * mygame = malloc(sizeof(game));
   mygame->cells = malloc(rows*cols*sizeof(cell));
 
   //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
   mygame->rows = rows;
   mygame->cols = cols;
   mygame->score = 0;
 
   int i;
   for(i = 0; i < rows*cols; i++) { //assign every element to be -1
       mygame->cells[i] = -1;
   }
 
   return mygame;
}
 
void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
   game structure to have the given number of rows and columns. Initialize
   the score and all elements in the cells to -1. Make sure that any
   memory previously allocated is not lost in this function.
*/
{
   /*Frees dynamically allocated memory used by cells in previous game,
    then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
   free((*_cur_game_ptr)->cells);
   (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
 
    //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
   // assign new values
   (*_cur_game_ptr)->rows = new_rows;
   (*_cur_game_ptr)->cols = new_cols;
   (*_cur_game_ptr)->score = 0;
   int i;
   for(i = 0; i < new_rows*new_cols; i++) { //reassign the array to be all empty
       (*_cur_game_ptr)->cells[i] = -1;
   }
 
   return;
}
 
void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
   This includes any substructures the game data structure contains. Do not modify this function.*/
{
   free(cur_game->cells);
   free(cur_game);
   cur_game = NULL;
   return;
}
 
cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
   cell on the game. (See game.h for game data structure specification)
   This function should be handy for accessing game cells. Return NULL
   if the row and col coordinates do not exist.
*/
{
   //YOUR CODE STARTS HERE
 
   if(row > cur_game->rows || col > cur_game->cols || row < 0 || col < 0) { //checks out of bounds
       return NULL;
   }
 
   return &cur_game->cells[(row * cur_game->cols) + col]; //returns address of cell which used as pointer
}
 
int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
  one above it, the tiles are merged by adding their values together. When
  tiles merge, increase the score by the value of the new tile. A tile can
  not merge twice in one turn. If sliding the tiles up does not cause any
  cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
   //YOUR CODE STARTS HERE
   int i;
   int j;
   int k;
   int isValid = 0;
 
   int rowz = cur_game->rows;
   int colz = cur_game->cols;
 
   for(i=0;i<colz;i++) { //every row
      
       for(j=0;j<rowz;j++) { //every col
           if(cur_game->cells[j*colz + i] != -1) { //cell not empty
           int merged = 0;
               for(k=j-1;k>=0;k--) { //find empty cell
                   if(get_cell(cur_game, k, i) == NULL) { // emergency break out because if k is negative it will not work
                       break;
                   }
                  
                   if (cur_game->cells[(k)*colz + i] == -1) { //found one
                       //copy from (i,j) into (k,j)
                       cur_game->cells[(k)*colz + i] = cur_game->cells[(k+1)*colz + i];
                       //erase value in (i,j)
                       cur_game->cells[(k+1)*colz + i] = -1;
                      
                       isValid = 1;
                      
                   } else
                   if(merged == 0 && cur_game->cells[(k)*colz + i] == cur_game->cells[(k+1)*colz + i]) { //if cell and cell abo
                       cur_game->cells[(k)*colz + i] *= 2; // change value appropriately
                       cur_game->cells[(k+1)*colz + i] = -1; // delete old cell
                      
                       isValid = 1;
                       merged = 1;
                   }
               }
           }
       }
   }
   return isValid;
 
};
 
int move_s(game * cur_game) //slide down
{
   //YOUR CODE STARTS HERE
   int i;
   int j;
   int k;
   int isValid = 0;
 
   int rowz = cur_game->rows;
   int colz = cur_game->cols;
 
   for(i=0;i<colz;i++) { //every col
  
       for(j=rowz;j>=0;j--) { //every row
           if(cur_game->cells[j*colz + i] != -1) { //cell not empty
           int merged = 0;
               for(k=j + 1;k<=rowz;k++) { //find empty cell
                  
                   if (cur_game->cells[(k)*colz + i] == -1) { //found one
                       //copy from (i,j) into (k,j)
                       cur_game->cells[(k)*colz + i] = cur_game->cells[(k-1)*colz + i];
                       //erase value in (i,j)
                       cur_game->cells[(k-1)*colz + i] = -1;
                      
                       isValid = 1;
 
                   } else
                   if(merged == 0 && cur_game->cells[(k)*colz + i] == cur_game->cells[(k-1)*colz + i]) { //if cell and cell above are same
                       cur_game->cells[(k)*colz + i] *= 2; // change value appropriately
                       cur_game->cells[(k-1)*colz + i] = -1; // delete old cell
                      
                       isValid = 1;
                       merged = 1;
                   }
               }
           }
       }
   }
   return isValid;
 
};
 
int move_a(game * cur_game) //slide left
{
   //YOUR CODE STARTS HERE
   int i;
   int j;
   int k;
   int isValid = 0;
 
   int rowz = cur_game->rows;
   int colz = cur_game->cols;
 
   for(i=0;i<rowz;i++) { //every row
   int merged = 0;
       for(j=0;j<colz;j++) { //every col
           if(cur_game->cells[i*colz + j] != -1) { //cell not empty
          
               for(k=j-1;k>=0;k--) { //find empty cell
                  
                   if (cur_game->cells[(i)*colz + k] == -1) { //found one
                       //copy from (i,j) into (k,j)
                       cur_game->cells[(i)*colz + k] = cur_game->cells[(i)*colz + k + 1];
                       //erase value in (i,j)
                       cur_game->cells[(i)*colz + k + 1] = -1;
                      
                       isValid = 1;
 
                   } else
                   if(merged == 0 && cur_game->cells[(i)*colz + k] == cur_game->cells[(i)*colz + k + 1]) { //if cell and cell above are same
                       cur_game->cells[(i)*colz + k] *= 2; // change val of combined cell to appropriate val
                       cur_game->cells[(i)*colz + k + 1] = -1; // delete old combined cell
                      
                       isValid = 1;
                       merged = 1;
                   }
               }
           }
       }
   }
   return isValid;
 
};
 
int move_d(game * cur_game){ //slide to the right
   //YOUR CODE STARTS HERE
   int i;
   int j;
   int k;
   int isValid = 0;
 
   int rowz = cur_game->rows;
   int colz = cur_game->cols;
 
   for(i=0;i<rowz;i++) { //every row
   int merged = 0;
       for(j=colz;j>=0;j--) { //every col
           if(cur_game->cells[i*colz + j] != -1) { //cell not empty
          
               for(k=j+1;k<colz;k++) { //find empty cell
                  
                   if (cur_game->cells[(i)*colz + k] == -1) { //found one
                       //copy from (i,j) into (k,j)
                       cur_game->cells[(i)*colz + k] = cur_game->cells[(i)*colz + k - 1];
                       //erase value in (i,j)
                       cur_game->cells[(i)*colz + k - 1] = -1;
                      
                       isValid = 1;
 
                   } else
                   if(merged == 0 && cur_game->cells[(i)*colz + k] == cur_game->cells[(i)*colz + k - 1]) { // if cells can be combined
                       cur_game->cells[(i)*colz + k] *= 2; //combine
                       cur_game->cells[(i)*colz + k - 1] = -1; // delete old cell
                      
                       isValid = 1;
                       merged = 1;
                   }
               }
           }
       }
   }
   return isValid;
 
};
 
int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
   no legal moves if sliding in any direction will not cause the game to change.
   Return 1 if there are possible legal moves, 0 if there are none.
*/
{
   //YOUR CODE STARTS HERE
   int rows = cur_game->rows;
   int cols = cur_game->cols;
 
   int originalCells[rows * cols];
   int i;
   for(i = 0; i < rows*cols; i++) {
       originalCells[i] = cur_game->cells[i];
   }
 
   int up = move_w(cur_game);
   int down = move_s(cur_game);
   int right = move_d(cur_game);
   int left = move_a(cur_game);
 
   if ((up==0) && (down==0) && (left==0) && (right==0)) {
     return 0;
   }
 
   for(i = 0; i < rows*cols; i++) {
       cur_game->cells[i] = originalCells[i];
   }
 
   return 1;
 
}
 
 
/*! code below is provided and should not be changed */
 
void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
 
   cell * cell_ptr;
   cell_ptr =     cur_game->cells;
 
   if (cell_ptr == NULL){
       printf("Bad Cell Pointer.\n");
       exit(0);
   }
 
 
   //check for an empty cell
   int emptycheck = 0;
   int i;
 
   for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
       if ((*cell_ptr) == -1){
               emptycheck = 1;
               break;
       }
       cell_ptr += 1;
   }
   if (emptycheck == 0){
       printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
       exit(0);
   }
 
   int ind,row,col;
   int num;
   do{
       ind = rand()%((cur_game->rows)*(cur_game->cols));
       col = ind%(cur_game->cols);
       row = ind/cur_game->cols;
   } while ( *get_cell(cur_game, row, col) != -1);
       //*get_cell(cur_game, row, col) = 2;
   num = rand()%20;
   if(num <= 1){
       *get_cell(cur_game, row, col) = 4; // 1/10th chance
   }
   else{
       *get_cell(cur_game, row, col) = 2;// 9/10th chance
   }
}
 
int print_game(game * cur_game)
{
   cell * cell_ptr;
   cell_ptr =     cur_game->cells;
 
   int rows = cur_game->rows;
   int cols = cur_game->cols;
   int i,j;
 
   printf("\n\n\nscore:%d\n",cur_game->score);
 
 
   printf("\u2554"); // topleft box char
   for(i = 0; i < cols*5;i++)
       printf("\u2550"); // top box char
   printf("\u2557\n"); //top right char
 
 
   for(i = 0; i < rows; i++){
       printf("\u2551"); // side box char
       for(j = 0; j < cols; j++){
           if ((*cell_ptr) == -1 ) { //print asterisks
               printf(" **  ");
           }
           else {
               switch( *cell_ptr ){ //print colored text
                   case 2:
                       printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 4:
                       printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 8:
                       printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 16:
                       printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 32:
                       printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 64:
                       printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 128:
                       printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 256:
                       printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 512:
                       printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 1024:
                       printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 2048:
                       printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 4096:
                       printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   case 8192:
                       printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                       break;
                   default:
                       printf("  X  ");
 
               }
 
           }
           cell_ptr++;
       }
   printf("\u2551\n"); //print right wall and newline
   }
 
   printf("\u255A"); // print bottom left char
   for(i = 0; i < cols*5;i++)
       printf("\u2550"); // bottom char
   printf("\u255D\n"); //bottom right char
 
   return 0;
}
 
int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
   int rows,cols;
   char buf[200];
   char garbage[2];
   int move_success = 0;
 
   switch ( input_char ) {
   case 'w':
       move_success = move_w(cur_game);
       break;
   case 'a':
       move_success = move_a(cur_game);
       break;
   case 's':
       move_success = move_s(cur_game);
       break;
   case 'd':
       move_success = move_d(cur_game);
       break;
   case 'q':
       destroy_game(cur_game);
       printf("\nQuitting..\n");
       return 0;
       break;
   case 'n':
       //get row and col input for new game
       dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
       while (NULL == fgets(buf,200,stdin)) {
           printf("\nProgram Terminated.\n");
           return 0;
       }
 
       if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
       rows < 0 || cols < 0){
           printf("Invalid dimensions.\n");
           goto dim_prompt;
       }
 
       remake_game(&cur_game,rows,cols);
 
       move_success = 1;
 
   default: //any other input
       printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
   }
 
 
 
 
   if(move_success == 1){ //if movement happened, insert new tile and print the game.
        rand_new_tile(cur_game);
        print_game(cur_game);
   }
 
   if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
       printf("Game Over!\n");
       return 0;
   }
   return 1;
}
 
 
 
 
 


