//
//  dynamArray.h
//  trove
//
//  Created by Joel Smith on 12/10/2022.
//

#ifndef dynamArray_h
#define dynamArray_h

#include <stdio.h>

typedef struct {
  char **array;
  size_t used;
  size_t size;
} Array;



void initArray(Array *a, size_t initialSize);

void insertArray(Array *a, int element);

void freeArray(Array *a);

void printArray(Array *a);

int checkArray(Array *a, char *string);



#endif /* dynamArray_h */
