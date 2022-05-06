//jacob tentis jtentis2
//Partners: agbalan2, aliceg3
//This program takes two numbers as input for the lower and upper bounds then prints all of the semiprime numbers between the bounds.
//The method for doing this is that it checks all numbers between the bounds then checks if there are two prime factors 
//If it determines there are two prime factors it prints the semiprime



#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
	return print_semiprimes(a, b);
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number){
	int n;
    	for(n = 2; n < number; n++) { // Loop through all #s
    	    if(number % n == 0) { // Checks if divisible by anything
     	       return 0; // Divisible = not prime
     	   }
   	 }
   	 return 1; // Not divisible = prime
	}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, k, r = 0;
    for(i = a; i <= b; i++) { // All nums a through b
        for(k = 2; k < i; k++) { // Go through the factors of the number
            if( (is_prime(k) == 1) && (i % k == 0) && (is_prime(i/k) == 1) ) { //
                printf("%d ", i);
                r = 1;
                break;
            }
        }
    }

    return r;
}



