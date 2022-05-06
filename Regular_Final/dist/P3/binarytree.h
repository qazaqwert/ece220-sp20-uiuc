/***************************
 *   binarytree.h
 ****************************/


struct node
{
  int d;
  struct node *left;
  struct node *right;
};

typedef struct node NODE;


NODE* newnode(void);
NODE* init_node(int d, NODE* p1, NODE* p2);
NODE* create_tree(int a[], int size );
void insert_node( int d1, NODE* p1 );  

int same_level(NODE* root, int node1, int node2);

