#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"


void print_matirx(int arr[][n]){
  for(int i = 0 ; i < n ; ++i){
    for(int j = 0; j < n ; ++j){
      printf("%d\t", arr[i][j]);
    }
    printf("\n");
  }
}


void init_1st_row(int arr[][n]){
  // Your code starts here
  int a;
for(a = 0; a < n; a ++){
  if(a==0)
  arr[0][a] = 0;
  else
  arr[0][a] = (rand()%100);
}
}


void init_1st_col(int arr[][n]){
  // Your code starts here
  int a;
for(a = 0; a < n; a ++){
  if(a==0)
  arr[a][0] = 0;
  else
  arr[a][0] = (rand()%100);
}
}


void build_matrix_max(int arr[][n]){
  // Your code starts here
int i = 1;
int j = 1;
while(i < n && j < n){
if(arr[i][j-1] < arr[i-1][j]){
  arr[i][j] = arr[i-1][j];
}
else{
  arr[i][j] = arr[i-1][j];
}
if(i == 1 && j != (n-1)){
  i = j+1;
  j = 1;
}
else if(j == (n-1)){
  j = i+1;
  i = n-1;
}
else{
i --;
j ++;
}
}
}


