#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"
#include <stdbool.h>

// TODO - Safety Algorithm goes here

bool isSafe(int *available, int **alloc, int **demand)
{
    int *work = cloneVector(available);
    int finish[numProc];
    int check;
    int vecCmp;
    int complete[numProc];
    int count = 0;
    for(int i=0; i<numProc; i++) {finish[i] = 0;}
    do {
        check = unfinished(finish);
        vecCmp = compareVectors(demand[check], work);
        if(!(check == -1) && vecCmp == 0){
            addVectors(alloc[check], work);
            finish[check] = 1;
            complete[count] = check;
            count++;
        }
    } while(!(check == -1) && vecCmp == 0);
    if(unfinished(finish) == -1){
        printf("SAFE\n");
        return true;
        
    }
    printf("UNSAFE\n");
    return false;
    

}

/**
 * Helper method to determine if there is an unfinished thread. If there is, it returns the index
 * of the first unfinished thread it finds. Returns -1 if all threads have finished.
 * @param finish the array to keep track of the state of all threads
 */
int unfinished(int finish[])
{
    for(int i=0; i<numProc; i++){
        if(finish[i] == 0){
            return i;
        }
    }
    return -1;
}