
//Alice Getmanchuk- aliceg3, Jerry Balan- agbalan2, Jacob Tentis- jtentis3

//We are implementing Conway's game of life
//We use three functions countLiveNeighbor, updateBoard, and aliveStable in order to do this
//We check the number of live members of each cell and then update the board accordingly
//(if a live cell has 2 or 3 live members, it stays alive, else it dies. And if a dead cell has exactly 3 members, it lives)
//
//

/*
* countLiveNeighbor
* Inputs:
* board: 1-D array of the current game board. 1 represents a live cell.
* 0 represents a dead cell
* boardRowSize: the number of rows on the game board.
* boardColSize: the number of cols on the game board.
* row: the row of the cell that needs to count alive neighbors.
* col: the col of the cell that needs to count alive neighbors.
* Output:
* return the number of alive neighbors. There are at most eight neighbors.
* Pay attention for the edge and corner cells, they have less neighbors.
*/

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
   int alive = 0;
   int row_s;
   int col_s;

   for (row_s = (row - 1); row_s <= (row + 1); row_s++) { //looping neighbor row of current cell from left to right neighbors
       if ((row_s >= 0) && (row_s < boardRowSize)){ //checking if current cell row is within row boundaries
           for (col_s = (col - 1); col_s <= (col + 1); col_s++){ //looping neighbor column of current cell from top to bottom neighbors
               if ((col_s >= 0) && (col_s < boardColSize)){ //checking if current cell column is within column boundaries
                   if ((row_s != row) || (col_s != col)) { //checking to see if current cell isn't the cell given
                       if (board[((boardColSize*row_s)+ col_s)] == 1) { //if neighbor is alive, increment alive count
                           alive++;
                       }
                   }
               }
           }
       }
   }
   return alive;
}

/*
* Update the game board to the next step.
* Input:
* board: 1-D array of the current game board. 1 represents a live cell.
* 0 represents a dead cell
* boardRowSize: the number of rows on the game board.
* boardColSize: the number of cols on the game board.
* Output: board is updated with new values for next step.
*/
void updateBoard(int* board, int boardRowSize, int boardColSize) {
   int area = boardRowSize*boardColSize;
   int copyb[area];
   int count = 0;
   int i, j, k;

   for(i = 0; i < area; i ++) { //creating deep copy of array 'board' in order to check neighbors based on unedited copy of game board
       copyb[i] = board[i];
   }
   for(j = 0; j < boardRowSize; j++) {
       for(k = 0; k < boardColSize; k++){
           count = countLiveNeighbor(copyb, boardRowSize, boardColSize, j, k); //checking number of alive members of cell row j and column k and storing number in count
           if ((copyb[(j*boardColSize + k)] == 1) && (count != 2) && (count != 3)) {
               board[j*boardColSize + k] = 0; //if cell in row j and col k is alive and does NOT have 2 or 3 live neighbors, the cell will die
           }
           if ((copyb[(j*boardColSize + k)] == 0) && (count == 3)) {
               board[j*boardColSize + k] = 1; //if cell in row j and col k is dead and has exactly 3 live neighbors, the cell will live
           }
       }
   }

}

/*
* aliveStable
* Checks if the alive cells stay the same for next step
* board: 1-D array of the current game board. 1 represents a live cell.
* 0 represents a dead cell
* boardRowSize: the number of rows on the game board.
* boardColSize: the number of cols on the game board.
* Output: return 1 if the alive cells for next step is exactly the same with
* current step or there is no alive cells at all.
* return 0 if the alive cells change for the next step.
*/
int aliveStable(int* board, int boardRowSize, int boardColSize){
   int r, c;
   for(r = 0; r < boardRowSize; r++) {
       for(c = 0; c < boardColSize; c++) {
           int count = countLiveNeighbor(board, boardRowSize, boardColSize, r, c); //checking number of neighbors of cell row r and column c
           if (((board[(r*boardColSize + c)] == 1) && (count != 2) && (count != 3)) || //if cell is alive and has NOT 2 or 3 alive neighbors, then means board will update
           ((board[(r*boardColSize + c)] == 0) && (count == 3))) {
               return 0; //since board will update, return 0
           }


       }
   }
   return 1; //returns 1 if board will not update
}




