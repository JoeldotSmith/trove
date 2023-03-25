//
//  CITS2002 Project 2 2022
//  Student1:   23338559   SMITH   JOEL   100
//
//  Created by Joel Smith on 8/10/2022.
//

#include "filelist.h"
#include "dynamArray.h"

#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <stdbool.h>
#include <ctype.h>

Array files;

void zip(int num, const char* trovename){//zip if 1, 0 if unzip
    if (num == 1) {
        char command[256] = "gzip ";
        strcat(command, trovename);
        system(command);
    }
    if (num == 0) {
        char command[256] = "gunzip ";
        strcat(command, trovename);
        system(command);
    }
}

void linedelete(const char* filename, int lineNum){
    FILE *fileptr1, *fileptr2;
    int ch;
    int delete_line = lineNum;
    int temp = 1;

    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    
    while (ch != EOF)//prints original file
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = getc(fileptr1);
    while (ch != EOF){//copies file
        if (ch == '\n')
            temp++;
            //except the line to be deleted
            if (temp != delete_line)
            {
                //copy all lines in file replica.c
                putc(ch, fileptr2);
            }
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
    printf("\n The contents of file after being modified are as follows:\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
}

int isDir(const char* name)// returns 0 if a directory
{
    struct stat path;

    stat(name, &path);

    return S_ISREG(path.st_mode);
}

void writeTrove(FILE *trove, char *f, int len){
    FILE *file = fopen(f, "r");
    char *code;
    int c;
    int count = 0;

    if (file == NULL){
        return;
    }  //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);
    char* fullPath = realpath(f, NULL);
    printf(" fullpath = %s, ", fullPath);
    fprintf(trove, "%s", fullPath);
    while ((c = fgetc(file)) != EOF) {
        if (isalnum(c)){//checking if it is alphanumeric
//            code[count] = (char)c;
            count += 1;
        }else{
            if (count>=len){
                code[count] = (char) '\0';
                fprintf(trove, " %s", code);
                
            }
            strcpy(code, "");
            count = 0;
            
        }
        
    }
    free(code);

    fprintf(trove, "\n");
    fclose(file);
}

void traverseDir(char *filename){
    char next[1000];
    struct dirent *dp;
    if (isDir(filename)==0){
        DIR *dir = opendir(filename);
        
        if (dir == NULL){//double check if its a directory can't be too safe
            return;
        }
        while ((dp = readdir(dir)) != NULL){
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
                    
                    strcpy(next, filename);
                    strcat(next, "/");
                    strcat(next, dp->d_name);
                    printf(" traversing ------  %s\n", next);
                    traverseDir(next);//recursion baby wooooo
            }
        }
        closedir(dir);
    }else{//if not directory must be a file and want to add that too files aswell
        if (checkArray(&files, filename) == 0){
                strcpy(files.array[files.used], filename);
                files.used += 1;
                if (files.used == files.size){
                    for (int i = 0; i < 100; i++)
                      insertArray(&files, i);
                }
            }
        }
    }

void buildTrove(const char *trovename, int length, Array filelist){
    
    initArray(&files, 20);
    FILE *trovefp;
    
    trovefp = fopen(trovename, "w+");
    
    for (int i = 0; i < filelist.used; i++){//for each name in filelist either traverse the directory and add files or just add files
        char * filename = filelist.array[i];
        // if name is a directory
        if (isDir(filename)==0){
            traverseDir(filename);
            for (int i = 0; i < files.used; i++){
                writeTrove(trovefp, files.array[i], length);
            }
        }else{
            writeTrove(trovefp, filename, length);
        }
        printArray(&files);
    }
    fclose(trovefp);
    freeArray(&files);
    zip(1, trovename);//zip it up
}

void removeTrove(const char *trovename, Array filelist){
    //for each line in trove{
    //check if filelist.array[i] == first word in line
    //if it is delete the whole line
    
    zip(0, trovename);//unzip
    
    FILE *file = fopen(trovename, "r+");
    char word[256];

    int line = 1;
    
    while (!feof(file)) {
            fscanf(file,"%s%*[^\n]",word);
            printf("\n\n line = %i \n\n", line);
        
        for (int i = 0; i < filelist.used; i++){
            printf("\n\nfilelist.array[i] =%s\nword = %s\n\n", filelist.array[i], word);
            if (strcmp(filelist.array[i], word)==0){
                
                linedelete(trovename, line);
                file = fopen(trovename, "r+");
                line = 1;
                break;
                }
            }
        
        line += 1;
        }
    fclose(file);
    zip(1, trovename);//rezip
}



void updateTrove(const char *trovename, Array filelist, int len){
    zip(0, trovename);//unzip
    removeTrove(trovename, filelist);//removing the name first
    FILE *trovefp;
    trovefp = fopen(trovename, "r+");
    for (int i = 0; i < filelist.used; i++){
        writeTrove(trovefp, filelist.array[i], len);//then adding it again
    }
    zip(1, trovename);//rezip
}
