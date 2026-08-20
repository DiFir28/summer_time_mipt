#include "cliprocessing.h"

#include <stdio.h>
#include <string.h>

#include "colors.h"

char *HELP_ARG = "--help";
char *HAND_WRITE_ARG = "-input";
char *FILE_READ_ARG = "-file";
char *TEST_ARG = "-test";

CLI_SCRIPTS getScript(int argc, char *argv[]){
    if (argc == 1 || argc > 3){        
        return INFO;
    }
    if (strcmp(argv[1], HELP_ARG) == 0){
        return HELP;
    }
    if(strcmp(argv[1], HAND_WRITE_ARG) == 0){
        return HAND_INPUT;
    }
    if (strcmp(argv[1], FILE_READ_ARG) == 0){
        if (argc != 3){
            printf(RED "You must give file name" DEFOULT_COLOR);
            return ERROR;
        }
        return FILE_INPUT;
    }
    if(strcmp(argv[1], TEST_ARG) == 0){
        return TESTING;
    }
    return ERROR;
}