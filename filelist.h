
//
//  filename.h
//  trove
//
//  Created by Joel Smith on 8/10/2022.
//

#ifndef filelist_h
#define filelist_h

#include <stdio.h>


#include "dynamArray.h"


void buildTrove(const char *trovename, int length, Array filelist);

void writeTrove(FILE *trove, char *f, int len);

void removeTrove(const char *trovename, Array filelist);

void updateTrove(const char *trovename, Array filelist, int len);

void linedelete(const char* filename, int lineNum);

int isDir(const char* name);

void traverseDir(char *filename);

void zip(int num, const char *trovename);


#endif /* filename_h */
