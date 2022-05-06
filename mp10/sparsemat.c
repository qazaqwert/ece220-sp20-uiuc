//MP10:
//Alice Getmanchuk (aliceg3), Jerry Balan (agbalan2), Jacob Tentis (jtentis2)
//In this MP, we wrote functions that helped take a sparse matrix and transform
//it into a list of tuples which are more efficient in storing the matrix
//We search the matrix for non-zero elements and store their location along
//value in a tuple. All the tuples are in order as they should be
 
 
#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
 
 
 
sp_tuples * load_tuples(char* input_file) //use set tuples
{
    sp_tuples *tup = malloc(sizeof(sp_tuples)); // allocate memory for matrix
    int row, col;
    FILE *readTuples = fopen(input_file, "r"); // open file to read
    if(readTuples == NULL) { //throw error just incase
        printf("NO FILE DETECTED"); //print so its visible to debug
        return NULL;
    }
    fscanf(readTuples, "%d %d", &row, &col); //Read the row and column
    // Initialize the matrix with basic information
    tup->m = row;
    tup->n = col;
    tup->nz = 0;
    tup->tuples_head = NULL;
 
    // Read each line until you reach the end of the file
    int nodeRow, nodeCol;
    double nodeVal;
    while(fscanf(readTuples, "%d %d %lf", &nodeRow, &nodeCol, &nodeVal) != EOF) {
        set_tuples(tup, nodeRow, nodeCol, nodeVal); // Correctly place each in the matrix linked list
    }
 
    // Close & return
    fclose(readTuples);
    return tup;
}
 
 
 
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    // Use the pointer to loop through the list of the matrix elements
    sp_tuples_node *ptr = mat_t->tuples_head;
    while(ptr != NULL) {
        // If correct element identified, return value
        if(ptr->row == row && ptr->col == col) { 
            return ptr->value;
        }
        ptr = ptr->next;
    }
    // Nothing in matrix list -> 0 because sparse matrix
    return 0;
}
 
 
 
void set_tuples(sp_tuples * mat_t, int row, int col, double value) 
{
    if(value == 0) {
        if(gv_tuples(mat_t, row, col) != 0) { // delete existing tuple
            sp_tuples_node *ptr = mat_t->tuples_head;
            sp_tuples_node *ptr_prev = NULL;
            // edge case where head needs to be deleted
            if(ptr != NULL && ptr->col == col && ptr->row == row) {
                mat_t->tuples_head = ptr->next;
                free(ptr);
            }
            //iterate to desired location where ptr is node that needs removal
            while(ptr != NULL && !(ptr->row == row && ptr->col == col)) { 
 
                ptr_prev = ptr;
                ptr = ptr->next;
            }
            if(ptr == NULL) {
                printf("Error, not found in matrix"); //print error
                return;
            }
            ptr_prev->next = ptr->next;
            mat_t->nz = mat_t->nz - 1; //update NZ
            free(ptr); // free memory
        } // deleting a tuple that already does not exist doesnt change anything
 
    } else { // add or replace value
        //create node and init
        sp_tuples_node *newNode = malloc(sizeof(sp_tuples_node));
        newNode->row = row;
        newNode->col = col;
        newNode->value = value;
        newNode->next = NULL;
 
        // make pointers to iterate with
        sp_tuples_node *ptr = mat_t->tuples_head;
        sp_tuples_node *ptr_prev = NULL;
 
        // check case of head being null
        if(mat_t->tuples_head == NULL || ptr->row > row || (ptr->row == row && ptr->col > col)) {
            newNode->next = mat_t->tuples_head;
            mat_t->tuples_head = newNode;
            mat_t->nz = mat_t->nz + 1; // update NZ
            return;
        }
        
        // traverse to desired location where if we want to replace node, we arrive at it
        // or if we want to insert, we are right in between
        while(ptr != NULL && (ptr->row < row || (ptr->row == row && ptr->col < col))) {
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        if(ptr != NULL && ptr->row == row && ptr->col == col) { // replace node as something exists here
            ptr_prev->next = newNode;
            newNode->next = ptr->next;
            free(ptr); // free the memory
            return;
        } else { // insert node as nothing exists here yet
            ptr_prev->next = newNode;
            newNode->next = ptr;
            mat_t->nz = mat_t->nz + 1; // update NZ
            return;
        }
    }
    return;
}
 
 
 
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    // Open file and ensure it exists
    FILE *writeTuples = fopen(file_name, "w");
    if(writeTuples == NULL) {
        printf("NO FILE DETECTED");
        return;
    }
    // Write the row and column at the top
    fprintf(writeTuples, "%d %d\n", mat_t->m, mat_t->n);
 
    //Use a pointer and iterate through the rest of the non zero matrix elements
    sp_tuples_node *ptr = mat_t->tuples_head;
    while(ptr != NULL) {
        fprintf(writeTuples, "%d %d %f\n", ptr->row, ptr->col, ptr->value);
        ptr = ptr->next;
    }
 
    // Close and return
    fclose(writeTuples);
    return;
}
 
 
 
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    if(matA->m != matB->m || matA->n != matB->n) { //case if matricies are not the same size
        return NULL; // addition is not possible
    }
 
    // Create and init new matrix
    sp_tuples *retmat = malloc(sizeof(sp_tuples));
    retmat->nz = 0;
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->tuples_head = NULL;
    
    // Create pointer and iterate through matA, adding to return matrix.
    sp_tuples_node *ptr = matA->tuples_head;
    while(ptr != NULL) {
        // calculate the result of each addition and put it as a new element in the return matrix
        double result = gv_tuples(retmat, ptr->row, ptr->col) + gv_tuples(matA, ptr->row, ptr->col);
        set_tuples(retmat, ptr->row, ptr->col, result);
        ptr = ptr->next;
    }
 
    // Create pointer and iterate through matA, adding to return matrix.
    ptr = matB->tuples_head;
    while(ptr != NULL) {
        // calculate the result of each addition and put it as a new element in the return matrix
        double result = gv_tuples(retmat, ptr->row, ptr->col) + gv_tuples(matB, ptr->row, ptr->col);
        set_tuples(retmat, ptr->row, ptr->col, result);
        ptr = ptr->next;
    }
 
    return retmat;
}
 
 
// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ // might do later
  return NULL;
}
 
 
    
void destroy_tuples(sp_tuples * mat_t){
    // Create a pointer and free all memory in the list by iterating through it
    sp_tuples_node *ptr = mat_t->tuples_head;
    while(ptr != NULL) {
        sp_tuples_node *ptrNext = ptr->next;
        free(ptr);
        ptr = ptrNext;        
    }
    // Free the matrix structure
    free(mat_t);
    return;
}  