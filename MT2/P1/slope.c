#include <stdio.h>
#include "slope.h"


// Return index of the first row that is not a slope; otherwise return -1
int find_nonslope_row(int array[6][6]) {
  // Your code starts here

int k = 0;
int l = 0;
int g;
int h;
for(g = 0; g < 6; g++){
  for(h = 0; h < 5; h++){
    int i = array[g][h];
    int j = array[g][h+1];
    if(i - j < 0)
      k++;
    
    if(i - j > 0)
      l++; 
    }
  if(k != 5 && l != 5)
  return(g);
  else{
    k = 0;
    l = 0;
  }
}
  return(-1);
}

int read_array(char* filename, int array[6][6]){
  // Your code starts here
  int a;
  int b;
  FILE *Myfile;
  Myfile = fopen(filename, "r");
  if(Myfile == NULL){
    return(0);
  }
  for(a = 0; a <= 5; a++){
    for(b = 0; b <= 5; b++){
      fscanf(Myfile, "%d", &array[a][b]);

    }
  }
  fclose(Myfile);
 return(1);
}

