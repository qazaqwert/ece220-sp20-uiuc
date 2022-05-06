#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "helpers.h"



int changeDate(node* head, int custID, int newDate){
//YOUR CODE STARTS HERE
while(head != NULL && head->cust->customerID != custID){
    head = head->next;
}
if(head != NULL){
    head->cust->orderDate = newDate;
    return(1);
}
else
{
    return(0);
}
    
}




void destroyList(node* head){
//YOUR CODE STARTS HERE
node *temp;
while(head != NULL){
    temp = head;
    free(temp->cust);
    free(temp);
    head = head->next;
    
    
}


}
