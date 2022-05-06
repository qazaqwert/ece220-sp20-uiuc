//Jacob Tentis - jtentis2 - ECE 220 - mp3 - 2/20/20
//This program calculates one row of pascal's triangle. The method it uses to do this is
//to fetch a user input for the row to compute, then it begins tracking the current number
//in the row from 0-row#. For the first digit and last digit (0, and row) it outputs a 1,
//for numbers in between that, it calculates the digit to print from the equation given

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;
  int i; 
  int k;
  int yeet;
  unsigned long sum;
  printf("Enter a row index: ");	//prompts user
  scanf("%d",&row);			//fetches user input for row #	
  // Write your code here
	for( yeet = 0; yeet < (row + 1); yeet = yeet + 1) //Tracks current digit in row, stops when all digits printed
	{
		sum = 1;
		if(yeet == 0 || yeet == row){ //for the first and last digits it prints 1
		}
		else{ //for all other digits, uses formula to calculate what to print
		i = 1;
		sum = 1;
		for( k = 0; k < yeet; k = k + 1){ 
			unsigned long eq = (sum * (row + 1 - i)); 	//formula
			sum = eq / i;					//formula
			i = (i + 1);
			}
		}

	printf("%lu ", sum); 	//prints current calculated digit, goes to calc next digit
	}

  return 0;			//ends after all digits printed
}
