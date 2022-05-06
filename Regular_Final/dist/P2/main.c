#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "helpers.h"




int main() {
/*main
Inputs: none

Outputs: arbitrary return value (integer)

Notes: Ungraded function for use by students to assist in coding
and debugging. May be edited freely by students.

*/

    /*call function that creates the linked list*/
    node* head = makeList();

    /*print original state of list*/
    printList(head);


    /*call student function change the orderDate, and print to check*/
    int ret = changeDate(head, 1003, 15640205);

    printf("\n------------Printing list after change---------\n\n");
    printList(head);

    /*call student function to free the memory used by the list*/
    destroyList(head);



  return ret;
}
