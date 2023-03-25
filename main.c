//
//  CITS2002 Project 2 2022
//  Student1:   23338559   SMITH   JOEL   100
//
//  Created by Joel Smith on 8/10/2022.
//


#include "trove.h"
#include "word.h"
#include "filelist.h"
#include "dynamArray.h"
 
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



int main(int argc, const char * argv[]) {
    
    const char *trovefName = ":tmp:trove";
    Array filelist;
    initArray(&filelist, 30);
    
    //command line checks
    bool build = false;
    bool remove = false;
    bool update = false;
    bool len = false;
    bool f = false;
    
    const char *word;
    
    int l = 4;//length of words
        
    int countCheck = 0;//checks if more than 1 -b -u or -r has been entered
    int fileLocCount = 0;
    
    for (int i = 0; i < argc; i++){
        
        const char *word = argv[i];
        
        
        printf("\n arg[%i] = %s", i, word);
        
        if (strcmp(word, "-f")==0){
            trovefName = argv[i+1];// getting values of value after -f ect. eg. -f /tmp/trove need the value after -f
            f = true;
            fileLocCount += 2;
        }
        if (strcmp(word, "-l")==0){
            l = atoi(argv[i+1]);
            len = true;
            fileLocCount += 2;
            
        }
        if (strcmp(word, "-b")==0){
            //build a trovefile with a file
            build = true;
            countCheck += 1;
            fileLocCount += 1;
            
            
        }
        if (strcmp(word, "-r")==0){
            //remove a file from a trovefile
            remove = true;
            countCheck += 1;
            fileLocCount += 1;
        }
        
        
        if (strcmp(word, "-u")==0){
            //update a file from a trovefile
            update = true;
            countCheck += 1;
            fileLocCount += 1;
        }
        
    }
    
    
    if (countCheck >= 2){
        printf("\n Error entered more than one -b || -r || -u please only enter 1\n");
        return -1;
    }
    
    
    if (build || remove || update || len){
        for (int j = fileLocCount+1; j < argc; j++){
            strcpy(filelist.array[filelist.used], argv[j]);
            filelist.used += 1;
            if (filelist.used == filelist.size){
                for (int i = 0; i < 100; i++)
                  insertArray(&filelist, i);
            }
          
        }
        printArray(&filelist);
        if (build){
            buildTrove(trovefName, l, filelist);
        }
        if (remove){
            removeTrove(trovefName, filelist);
        }
        if (update){
            updateTrove(trovefName, filelist, l);
        }
    } else {//if not build, update, remove it must be a word search call
        if (f){
            word = argv[3];
        } else{
            word = argv[1];
        }
        findWord(trovefName, word);
    }
    
    
    
    freeArray(&filelist);//make sure to free memory
    
    
    
    
    
    
    return 0;
}
