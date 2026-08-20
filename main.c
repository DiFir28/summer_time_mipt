#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "quade.h"

#define FLAG_HELP "help"
#define FLAG_DATA_FROM_FILE "file"

bool mainTask(){
    Quadratic Equat = initQuadratic();
    if (inputQuadratic(&Equat)){
        printf("Incorrect input.\n");
        return 1;
    }

    solveQuadratic(&Equat);
    printRoots(&Equat);
    return 0;
}


int main(int argc, char *argv[]){

    if (argc == 1){        
        return mainTask();
    }

    if (strcmp(argv[1], FLAG_HELP) == 0){
        printf("You need help");
    }else 
    if (strcmp(argv[1], FLAG_DATA_FROM_FILE) == 0){
        if (argc != 3){
            printf("You must give file name");
            return 2;
        }

        FILE *file = fopen(argv[2], "r");
        if (file == NULL){
            printf("No file in directory");
            return 3;
        }
        Quadratic Equat = initQuadratic();
        int count_flag = fscanf(file, "%lf %lf %lf", &Equat.a, &Equat.b, &Equat.c);
        if (count_flag != 3){
            printf("Inc %i", count_flag);
            return 4;
        }
        solveQuadratic(&Equat);
        printRoots(&Equat);
        fclose(file);
    }




    return 0;
}