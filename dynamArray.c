//
//  CITS2002 Project 2 2022
//  Student1:   23338559   SMITH   JOEL   100
//
//  Created by Joel Smith on 12/10/2022.
//

#include "dynamArray.h"
#include <stdlib.h>
#include <string.h>

void initArray(Array *a, size_t initialSize) {
  a->array = (char **) calloc(initialSize, sizeof(char *));
  if (a->array == NULL) exit(1);
  for(int i=0; i<initialSize; i++){
      a->array[i]=malloc(256*sizeof(char));
      if (a->array[i] == NULL) exit(1);
  }
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size
  if (a->used == a->size) {
    a->size *= 2;
      a->array = realloc(a->array, a->size * sizeof(char *));
      for(size_t i=(a->size)/2 + 1; i<a->size; i++){
          a->array[i]=calloc(256, sizeof(char));
      }
  }
    a->array[a->used++] = a->array[element];
}

void printArray(Array *a) {
    printf("\n\n");
    for (int i = 0; i < a->used; i++){
        printf(" ARRAY[%i] %s, \n", i, a->array[i]);
    }
    printf("\n\n");
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int checkArray(Array *a, char *string){//0 if not in array
    if (a->used == 0){
        return 0;
    }
    for (int i = 0; i < a->used; i++){
        if(strcmp(a->array[i], string)==0){
            return 1;
        }
    }
    
    return 0;
}
