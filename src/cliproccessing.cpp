#include "cliprocessing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

const char *HELP_ARG = "--help";
const char *HAND_WRITE_ARG = "--input";
const char *FILE_READ_ARG = "--file";
const char *TEST_ARG = "--test";
const char *PARS_ARG = "--pars";
const char *COUNT_ARG = "-c";

CLI_FLAG getCliFlags(int argc, char *argv[]){
    CLI_FLAG output = {};
    output.input_count = 1;
    //strcmp something
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], HELP_ARG) == 0){
            output.main_flag = CLI_HELP;
        }
        if(strcmp(argv[i], HAND_WRITE_ARG) == 0){
            if(output.input_type_flag){
                output.main_flag = CLI_ERROR;
                break;
            }
            output.input_type_flag = true;
            output.main_flag = CLI_CODE;
            output.input_type = HAND_INPUT;
        }
        if(strcmp(argv[i], PARS_ARG) == 0){ // TODO else if
            if(output.input_type_flag){
                output.main_flag = CLI_ERROR;
                break;
            }
            output.input_type_flag = true;
            output.main_flag = CLI_CODE;
            output.input_type = PARS_INPUT;
        }
        if (strcmp(argv[i], FILE_READ_ARG) == 0){
            if(output.file_flag || output.input_type == TEST_INPUT){
                output.main_flag = CLI_ERROR;
                break;
            }
            if (i+1 >= argc){
                printf(RED "You must give file name\n" DEFAULT_COLOR);
                output.main_flag = CLI_FILE_ERROR;
                break;
            }
            output.main_flag = CLI_CODE;
            if (!(output.input_type_flag)){
                output.input_type = HAND_INPUT;
            }
            output.file_flag = true;
            i++;
            output.file_name_index = i;
        }        
        if(strcmp(argv[i], COUNT_ARG) == 0){
             if (i+1 < argc){
                char **endN = NULL;
                long raw_n = strtol(argv[i+1], endN, 10);
                if (endN == NULL || &(argv[i+1]) != endN){
                    output.input_count = raw_n;
                    i++;
                }
            }
        }
        if(strcmp(argv[i], TEST_ARG) == 0){
            if(output.input_type_flag){
                output.main_flag = CLI_ERROR;
                break;
            }
            output.input_type_flag = true;

            output.main_flag = CLI_CODE;
            output.input_type = TEST_INPUT;
        }
    }
    return output;
}