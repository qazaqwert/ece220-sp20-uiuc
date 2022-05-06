#include <stdio.h>
#include "Search.h"

//Your implementation of this function must be recursive
//return 1 if item found in data; otherwise, return 0
int Search(int item, int data[ROW][COL], int start_row, int end_row, int start_col, int end_col){
    //Your code starts here
    if((start_row > end_row) || (start_col > end_col))
    return(0);

    if(start_col != end_col){                                                   //finding the column containing the item
    int midcol = (start_col + (end_col - 1)/2);                                 //Finding middle column
        if((data[0][midcol])==item)                                             //If by god we are lucky enough to have the item in row 0, this accounts for that
            return(1); 
        else if((data[0][midcol]) > item){                                      //if the current piece of data is larger than the item
            return Search(item, data, start_row, end_row, start_col, midcol-1);   //binary searches upstream
        }
        else{                                                                   //if the current piece of data is smaller than the item
            return Search(item, data, start_row, end_row, midcol+1, end_col);     //binary searches downstream
        }
        
    } 
    else{
        int midrow = (start_row + (end_row - 1)/2);
        if((data[midrow][start_col])==item) 
            return(1); 
        else if((data[midrow][start_col]) > item){                              //if the current piece of data is larger than the item
            return Search(item, data, start_row, midrow-1, start_col, end_col);   //binary searches upstream
        }
        else{                                                                   //if the current piece of data is smaller than the item
            return Search(item, data, midrow+1, end_row, start_col, end_col);     //binary searches downstream
        }

    }
    
}


