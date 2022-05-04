#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"
#include <stdbool.h>

bool isSafe(int *available, int **alloc)
{
    int *work = cloneVector(available);
    int finish[numProc];    //keeps track of which thread(s) have finished
    int complete[numProc];  //holds index of each thread that has been completed
    int count = 0;          //counter to make sure a finished thread id gets added to the correct slot
    for(int i=0; i<numProc; i++) {finish[i] = 0;}

    while(unfinished(finish, work) != -1){
        int index = unfinished(finish, work);
        addVectors(alloc[index], work);
        finish[index] = 1;
        complete[count] = index;  
        count++;
        calcNeed();
    }

    if(allFinished(finish)){
        printf("SAFE: ");
        for(int i=0; i<numProc; i++){
            printf("T%d ", complete[i]);
        }
        printf("\n");
        return true;
        
    }
    else {
        printf("UNSAFE: ");
        for(int i=0; i<numProc; i++){
            if(finish[i]==0){
                printf("T%d ", i);
            }
        }
        printf("can't finish\n");
        return false;
    }
    

}

/**
 * Helper method to determine if there is an unfinished thread. If there is, it returns the index
 * of the first unfinished thread it finds. Returns -1 if all threads have finished.
 * @param finish the array to keep track of the state of all threads
 */
int unfinished(int finish[], int *work)
{
    for(int i=0; i<numProc; i++){
        if((finish[i] == 0) && (compareVectors(need[i], work))==0){
            return i;
        }
    }
    return -1;
}

/**
 * Scans the finish array to see if any thread was unable to finish.
 * Used after making it through the main while loop in isSafe();
 * @param finish the array to check
 */
bool allFinished(int *finish)
{
    for(int i=0; i<numProc; i++){
        if(finish[i]==0){
            return false;
        }
    }
    return true;
}