#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <string.h>

// TODO - Define vector and matrix operations

/**
 * Helper function to initialize the necessary vectors/matrices
 * @param numRes the number of resources
 * @param numProc the number of processes
 */
void init(int numRes, int numProc) 
{
    printf("entered init");
    resourceVector = (int*)malloc(sizeof(int*)*numRes);

    demand = (int**)malloc(sizeof(int*)*numProc);
	for(int i=0; i<numRes; i++) {
		demand[i] = (int*)malloc(sizeof(int)*numRes);
	}

    alloc = (int**)malloc(sizeof(int*)*numProc);
    for(int i=0; i<numRes; i++) {
        alloc[i] = (int*)malloc(sizeof(int)*numRes);
    }
}

/**
 * free memory aassociated with all vectors/matrices
 */
void freeup() 
{
    free(resourceVector);
    free(demand);
    free(alloc);
}

/**
 * print the contents of a given vector
 * @param vector the vector to be printed
 */ 
void printVector(int *vector)
{
    for(int i=0; i<numRes; i++){
        printf("%d ", vector[i]);
    }
}

/**
 * print the contents of a given matrix
 * @param matrix the matrix to be printed
 */ 
void printMatrix(int **matrix)
{
    printf("entered print");
    for(int i=0; i<numProc; i++){
        for(int j=0; j<numRes; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * add two vectors together
 * @param vec1 the vector to be added to the second vector
 * @param vec2 the vector to be added to
 */
void addVectors(int *vec1, int *vec2)
{
    for(int i=0; i<numRes; i++) {
        vec2[i]+=vec1[i];
    }
}

/**
 * subtract one vector from another
 * @param vec1 the vector to be subtracted from the other vector
 * @param vec2 the vector the be subtracted from
 */
void subractVectors(int *vec1, int *vec2) 
{
    for(int i=0; i<numRes; i++){
        vec2[i]-=vec1[i];
    }
}

/**
 * compares two vectors. Returns 0 if they are equal and -1 otherwise
 * @param vec1 the first vector to be compared
 * @param vec2 the second vector to be compared
 */
int compareVectors(int *vec1, int *vec2)
{
    for(int i=0; i<numRes; i++){
        if(!(vec1[i]==vec2[i])){
            return -1;
        }
    }
    return 0;
}

/**
 * creates a copy of the given matrix
 * @param matrix the matrix to be cloned
 */
int** clone(int **matrix)
{
    int **copy;
    copy = (int**)malloc(sizeof(int*)*numProc);
	for(int i=0; i<numRes; i++) {
		copy[i] = (int*)malloc(sizeof(int)*numRes);
	}
    //memcpy(copy, matrix, numProc*numRes*sizeof(int));
    return copy;
}
