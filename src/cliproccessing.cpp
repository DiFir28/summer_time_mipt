#include "cliprocessing.h"

#include <stdio.h>
#include <string.h>

#include "colors.h"




const char *HELP_ARG = "--help";
const char *HAND_WRITE_ARG = "--input";
const char *FILE_READ_ARG = "--file";
const char *TEST_ARG = "--test";
const char *PARS_ARG = "--pars";


CLI_SCRIPTS getScript(int argc, const char *argv[]){
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
            printf(RED "You must give file name" DEFAULT_COLOR);
            return ERROR;
        }
        return FILE_INPUT;
    }
    if(strcmp(argv[1], TEST_ARG) == 0){
        return TESTING;
    }
    if(strcmp(argv[1], PARS_ARG) == 0){
        return PARS;
    }
    return ERROR;
}