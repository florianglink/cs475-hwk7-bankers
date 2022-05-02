#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

int main(int argc, char *argv[])
{
  printf("entered main");
  if(argv[1] == NULL){                 //make sure a file name was provided
    printf("Error: No file name provided\n");
  }
  else {
    char *filename = argv[1];
    FILE* file = fopen(filename, "r");
    if(file == NULL) {                 //make sure file exists
      printf("Error: File doesn't exist\n");
    }
    else {
      printf("entered else");
      fscanf(file, "%d", &numRes);  //grab number of resources
      fscanf(file, "%d", &numProc); //grab number of processes
      init(numRes, numProc);        //initialize all vectors/matrices
      for(int i=0; i<numRes; i++) {
        fscanf(file, "%d", &resourceVector[i]); //scan values into the resource vector
      }
      for(int j=0; j<numProc; j++){
        for(int k=0; k<numRes; k++){
          fscanf(file, "%d", &demand[j][k]);     //scan values into the demand matrix
        }
      }
      for(int l=0; l<numProc; l++){
        for(int m=0; m<numRes; m++){
          fscanf(file, "%d", &alloc[l][m]);      //scan values into the allocation matrix
        }
      }
      //printMatrix(alloc);
      //printVector(resourceVector);
      //int **work = clone(alloc);
      //printMatrix(work);
    }
  }


  // TODO: Run banker's safety algorithm
  return 0;
}
