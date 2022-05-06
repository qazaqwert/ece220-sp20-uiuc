#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
// partners: Jerry Balan (agbalan2), Alice Getmanchuk (aliceg3), Jacob Tentis (jtentis2)
// Mp9 - Maze
// In this program, we read a file with a width and height and a maze and parse it into a maze struct given to us.
// We have to use dynamic memory allocation to account for mazes of different widths and heights and keeping the ability
// to store and access them in 2D arrays. We also have to solve the maze by recursively calling the solve function with
// updated current positions. We have to check if each position is valid along the way.
 
 
/*
* createMaze -- Creates and fills a maze structure from the given file
* INPUTS:       fileName - character array containing the name of the maze file
* OUTPUTS:      None
* RETURN:       A filled maze structure that represents the contents of the input file
* SIDE EFFECTS: None
*/
maze_t *createMaze(char *fileName)
{
   // Your code here. Make sure to replace following line with your own code.
   int i, j; // loop iterator variables
   
   maze_t *maze = malloc(sizeof(maze_t)); // allocate mem for struct
   
   FILE *mazeFile = fopen(fileName, "r"); // open file
 
 
   int height = 0;
   int width = 0;
 
   fscanf(mazeFile, "%d", &width); // read width
   fscanf(mazeFile, "%d", &height); //read height
   maze->height = height; //initialize height
   maze->width = width; // initialize width
       // assign memeory for cells 2d array
   maze->cells = (char**)malloc(maze->height*sizeof(char*)); // allocate mem for the array holding the arrays
   for(i = 0; i < maze->height; i++) { //iterate through the array of pointing to each individual array and initialize it
       maze->cells[i] = (char*)malloc(maze->width*sizeof(char));
   }
 
    fgetc(mazeFile); // Read and ignore new line char
   for (i = 0; i < maze->height; i++) // iterate through each row
   {
       for (j = 0; j < maze->width; j++) // iterate cols
       {
           maze->cells[i][j] = fgetc(mazeFile); // get value from file and put in cells
           if(maze->cells[i][j] == START) { // initialize correct start
               maze->startColumn = j;
               maze->startRow = i;
           } else if(maze->cells[i][j] == END) { //initialize correct end
               maze->endColumn = j;
               maze->endRow = i;
           }
       }
       fgetc(mazeFile); // read and ignore new line char
 
   }
   fclose(mazeFile); //free file pointer
   
 
   return maze;
}
 
/*
* destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
* INPUTS:        maze -- pointer to maze structure that contains all necessary information
* OUTPUTS:       None
* RETURN:        None
* SIDE EFFECTS:  All memory that has been allocated for the maze is freed
*/
void destroyMaze(maze_t *maze)
{
    // Your code here.
    int i;
   for(i = 0; i < maze->height; i++) { //iterate in the pointer array to free each indiv array
       free(maze->cells[i]); 
   }
   free(maze->cells); //free “pointer array”
   free(maze); //free struct
   maze = NULL;
   return;
}
 
/*
* printMaze --  Prints out the maze in a human readable format (should look like examples)
* INPUTS:       maze -- pointer to maze structure that contains all necessary information
*               width -- width of the maze
*               height -- height of the maze
* OUTPUTS:      None
* RETURN:       None
* SIDE EFFECTS: Prints the maze to the console
*/
void printMaze(maze_t *maze)
{
   // Your code here.
   int col = maze->width;
   int row = maze->height;
   int i;
   int j;
 
   for(i=0; i<row; i++) { //iterate rows
       for(j=0; j<col; j++) { //iterate cols
           printf("%c", maze->cells[i][j]); // print cells one by one
       }
       printf("\n"); // split up for readability
   }
   return;
}
 
/*
* solveMazeManhattanDFS -- recursively solves the maze using depth first search,
* INPUTS:               maze -- pointer to maze structure with all necessary maze information
*                       col -- the column of the cell currently beinging visited within the maze
*                       row -- the row of the cell currently being visited within the maze
* OUTPUTS:              None
* RETURNS:              0 if the maze is unsolvable, 1 if it is solved
* SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
*/
int solveMazeDFS(maze_t *maze, int col, int row)
{
   // Your code here. Make sure to replace following line with your own code.
 
   // ensure row and col are valid
   if((maze->width <= col) || (maze->height <= row) || (row < 0) || (col < 0)) { 
       return 0;
   }
 
   // Excluding START and END, ensure current location is valid (not in a wall)
   if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != START && maze->cells[row][col] != END) {
       return 0; 
   }
 
   // Check if we reached END
   if(maze->cells[row][col] == END) {
       maze->cells[maze->startRow][maze->startColumn] = START; //reset START position to 'S'
       return 1;
   }
 
   // Set current position to final path
   maze->cells[row][col] = PATH;
 
   // Recursively call to the left of the current position
   if(solveMazeDFS(maze, col - 1, row) == 1) { //left of
       return 1;
   }
 
   // Recursively call to the right of the current position
   if(solveMazeDFS(maze, col + 1, row) == 1) { //right of
       return 1;
   }
 
   // Recursively call above the current position
   if(solveMazeDFS(maze, col, row - 1) == 1) { //above
       return 1;
   }
 
   // Recursively call below the current position
   if(solveMazeDFS(maze, col, row + 1) == 1) { //below
       return 1;
   }
 
   // If none of the above pass, mark the current position as VISITED instead of the solution path and return 0 to indicate failure
   maze->cells[row][col] = VISITED;
   return 0;
   
}