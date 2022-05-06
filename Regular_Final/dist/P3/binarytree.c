/**********************
 *  binarytree.c:
 ************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

NODE* new_node()
{ 
  return ((NODE*)malloc(sizeof(NODE)));
}

NODE* init_node(int d1, NODE* p1, NODE* p2)
{ 
  NODE* t;
  
  t = new_node();
  t->d = d1;
  t->left = p1;
  t->right = p2;
  return t;
}


void insert_node( int d1, NODE* p1 ){
  if( p1->d < d1 && p1->right == NULL )
    p1->right = init_node( d1, NULL, NULL );
  else if( p1->d > d1 && p1->left == NULL )
    p1->left = init_node( d1, NULL, NULL );
  else if( p1->d < d1 && p1->right != NULL )
    insert_node( d1, p1->right );
  else
    insert_node( d1, p1->left );
}


/* create a binary search tree from an array */
NODE* create_tree(int a[], int size )
{
  int i ;
  NODE* root = init_node( a[0] , NULL , NULL );

  for( i = 1 ; i < size ; i ++ )
    insert_node( a[i] , root  );

  return root;
}

// Return 1: if they are at the same level
// Return 0: if they are at different levels
int same_level(NODE* root, int node1, int node2) {
  // Write your code here!
NODE* n1s = root;
int c1 = 0;
NODE* n2s = root;
int c2 = 0;
while(n1s->d != node1){
  if(n1s->d < node1){
    n1s = n1s->right;
  }
  else if(n1s->d > node1){
  n1s = n1s->left;
  }
c1 = c1 + 1;
}

while(n2s->d != node2){
  if(n2s->d < node2){
    n2s = n2s->right;
  }
  else if(n2s->d > node2){
  n2s = n2s->left;
  }
c2 = c2 + 1;
}
if(c1 == c2){
  return(1);
}
else{
  return(0);
}
} 

