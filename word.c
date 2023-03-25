//
//  CITS2002 Project 2 2022
//  Student1:   23338559   SMITH   JOEL   100
//
//  Created by Joel Smith on 8/10/2022.
//

#include "word.h"
#include "dynamArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findWord(const char *trovename, const char *word){
    
    FILE *file = fopen(trovename, "r");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    
    Array filesThatHaveTheWord;
    initArray(&filesThatHaveTheWord, 20);
    
    line_size = getline(&line_buf, &line_buf_size, file);

      while (line_size >= 0){
          line_count++;
          char * token = strtok(line_buf, " ");
          char *filepath = token;
             
             while( token != NULL ) {//splitting each line into tokens of its words and comparing
                 
                 if (strcmp(token, word)==0){
                     if (checkArray(&filesThatHaveTheWord, filepath)==0){
                         strcpy(filesThatHaveTheWord.array[filesThatHaveTheWord.used], filepath);
                         filesThatHaveTheWord.used += 1;
                         if (filesThatHaveTheWord.used == filesThatHaveTheWord.size){
                             for (int i = 0; i < 100; i++)
                               insertArray(&filesThatHaveTheWord, i);
                         }
                     }
                 }
              
                token = strtok(NULL, " ");
             }

        line_size = getline(&line_buf, &line_buf_size, file);
    }
    free(line_buf);
    line_buf = NULL;
    fclose(file);
    if (filesThatHaveTheWord.used > 0){
        printf("\n\n Files containing the word:");
        for (int i = 0; i < filesThatHaveTheWord.used; i++){
            printf("\n%s", filesThatHaveTheWord.array[i]);
        }
    } else{
        printf("\n\n No files indexed contains that word.");
    }
    freeArray(&filesThatHaveTheWord);
    
}
    
