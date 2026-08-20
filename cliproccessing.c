#include "cliprocessing.h"

#include <stdio.h>
#include <string.h>

CLI_SCRIPTS getScript(int argc, char *argv[]){
    if (argc == 1){        
        return INFO;
    }

    if (strcmp(argv[1], HELP_ARG) == 0){
        return HELP;
    }else 
    if(strcmp(argv[1], HAND_WRITE_ARG) == 0){
        return HAND_INPUT;
    }else
    if (strcmp(argv[1], FILE_READ_ARG) == 0){
        if (argc != 3){
            printf("You must give file name");
            return ERROR;
        }
        return FILE_INPUT;
    }
}