#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "helpers.h"



void printCustomer(customer* c) {
/*
printCustomer
    Task: pretty-print the customer object's attributes

    Input: pointer to customer struct

    Output: none

    Side effects: prints information in the customer struct to stdout

    Notes: Ungraded function for use in student coding/debugging.
        Feel free to edit.
*/
    printf("CustomerID: %d\nOrderDate: %d\n", c->customerID , c->orderDate);
}


void printList(node* head) {
/*
printList
    Task: pretty-print the linked list and the associated information to stdout

    Input: pointer to list's head node

    Output: none
    
    Side effects: prints to stdout

    Notes: Ungraded function for use in student debugging and testing.
        Feel free to edit.
*/
    node *curr = head;
    while (curr != NULL) {
        printCustomer(curr->cust);
        printf("\t |\n\t |\n\t\\/\n");
        curr = curr->next;
    }
    printf("\tNULL\n");
}



node* makeList() {
/*
makeList
    Task: dynamically allocate a linked list that is sorted by increasing
        customerID number for the customer pointed to by the node (see list.h
        for how nodes and customers are defined).

    Input: none

    Output: a pointer to the head node of the linked list

    Notes: Ungraded function available for student use in coding and debugging.
        Feel free to edit.

*/
    //allocate the nodes
    node * n0 = (node*)malloc(sizeof(node));
    node * n1 = (node*)malloc(sizeof(node));
    node* n2 = (node*)malloc(sizeof(node));
//set the next pointers
    n0->next = n1;
    n1->next = n2;
    n2->next = NULL;
//allocate the customer structs and initialize their data
    customer* c0 = (customer*)malloc(sizeof(customer));
    c0->orderDate = 19990804;
    c0->customerID = 65;
    customer* c1 = (customer*)malloc(sizeof(customer));
    c1->orderDate = 20071105;
    c1->customerID = 98;
    customer* c2 = (customer*)malloc(sizeof(customer));
    c2->orderDate = 19960908;
    c2->customerID = 1003;

// insert customers into nodes
    n0->cust = c0;
    n1->cust = c1;
    n2->cust = c2;
//return head node
    return n0;

}
