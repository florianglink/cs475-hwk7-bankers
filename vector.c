#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <string.h>

/**
 * Helper function to initialize the necessary vectors/matrices
 * @param numRes the number of resources
 * @param numProc the number of processes
 */
void init(int numRes, int numProc) 
{
    resourceVector = (int*)malloc(sizeof(int*)*numRes);
    available = (int*)malloc(sizeof(int*)*numRes);

    demand = (int**)malloc(sizeof(int*)*numProc);
	for(int i=0; i<numProc; i++) {
		demand[i] = (int*)malloc(sizeof(int)*numRes);
	}

    alloc = (int**)malloc(sizeof(int*)*numProc);
    for(int i=0; i<numProc; i++) {
        alloc[i] = (int*)malloc(sizeof(int)*numRes);
    }

    need = (int**)malloc(sizeof(int*)*numProc);
    for(int i=0; i<numProc; i++) {
        need[i] = (int*)malloc(sizeof(int*)*numRes);
    }
}

/**
 * free memory associated with all vectors/matrices
 */
void freeup() 
{
    free(resourceVector);
    free(demand);
    free(alloc);
    free(available);
    free(need);
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
    printf("\n");
}

/**
 * print the contents of a given matrix
 * @param matrix the matrix to be printed
 */ 
void printMatrix(int **matrix)
{
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
 * compares two vectors. Returns 0 if all values in vector 1 are less than or equal to
 * vector 2 and -1 otherwise
 * @param vec1 the first vector to be compared
 * @param vec2 the second vector to be compared
 */
int compareVectors(int *vec1, int *vec2)
{
    for(int i=0; i<numRes; i++){
        if(vec1[i]>vec2[i]){
            return -1;
        }
    }
    return 0;
}

/**
 * creates a copy of the given matrix
 * @param matrix the matrix to be cloned
 */
int** cloneMatrix(int **matrix)
{
    int **copy;
    copy = (int**)malloc(sizeof(int*)*numProc);
	for(int i=0; i<numProc; i++) {
		copy[i] = (int*)malloc(sizeof(int)*numRes);
	}
    for(int j=0; j<numProc; j++){
        for(int k=0; k<numRes; k++){
            copy[j][k] = matrix[j][k];
        }
    }
    return copy;
}

/**
 * Creates a copy of the given vector
 * @param vector the cector to be cloned
 */
int* cloneVector(int *vector)
{
    int *copy;
    copy = (int*)malloc(sizeof(int*)*numRes);
    for(int i=0; i<numRes; i++){
        copy[i] = vector[i];
    }
    return copy;
}

/**
 * Calculates the current amount of each resource that is available.
 *  
 */
void calcAvailable()
{
    for(int i=0; i<numRes; i++){
        available[i] = resourceVector[i];
    }
    for(int i=0; i<numProc; i++){
        subractVectors(alloc[i], available);
    }
}

/**
 * Calculates the need matrix
 */
void calcNeed()
{
    need = cloneMatrix(demand);
    for(int i=0; i<numProc; i++){
        subractVectors(alloc[i], need[i]);
    }
}

/**
 * Conducts a sanity check to make sure that allocated resources don't exceed total resources
 * or that allocated resources exceed demand for a certain process
 */
int integrityTest()
{
    int *resources = cloneVector(resourceVector);
    for(int i=0; i<numRes; i++) {
        for(int j=0; j<numProc; j++) {
            resources[i] -= alloc[i][j];
            if(resources[i] < 0){
                printf("Integrity test failed: allocated resources exceed total resources\n");
                return -1;
            }
            if(alloc[i][j] > demand[i][j]){
                printf("Integrity test failed: allocated resources exceed demand for thread %d\n", i);
                return -1;
            }
        }
    }
    return 0;
}

/**
 * Reset a given matrix to zeros
 */
void resetMatrix(int **matrix)
{
	for(int i=0; i<numProc; i++) {
		for(int j=0; j<numRes; j++) {
			matrix[i][j] = 0;
		}
	}
}

/**
 * Reset a given vector to zeros
 */ 
void resetVector(int *vec)
{
    for(int i=0; i<numRes; i++){
        vec[i] = 0;
    }
}