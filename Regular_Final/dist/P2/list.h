#ifndef LIST_H
#define LIST_H




typedef struct{
    int customerID;
    int orderDate;
}customer;


typedef struct node{
    customer *cust;
    struct node *next;
}node;


int changeDate(node* head, int custID, int newDate);


void destroyList(node* head);











#endif
