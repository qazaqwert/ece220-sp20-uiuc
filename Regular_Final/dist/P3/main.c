
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"

int main(void)
{
  int a[9] = {10,5,11,3,8,6,9,15,13};
  NODE* root;
  root = create_tree(a, 9); 

  int node1 = -1; 
  int node2 = -1; 

  printf("Enter two nodes (numbers): ");
  scanf("%d %d", &node1 , &node2);
  //scanf("%d %d", &node1 , &node2);


  if(same_level(root, node1, node2)) {
    printf("Node %d and Node %d are at the same level\n", node1, node2);
  }
  else {
    printf("Node %d and Node %d are at different levels\n", node1, node2);
  }

  return 0;
}

