#include "cliprocessing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

const char *HELP_ARG = "--help";
const char *HAND_WRITE_ARG = "--hand";
const char *FILE_READ_ARG = "--file";
const char *TEST_ARG = "--test";
const char *PARS_ARG = "--pars";
const char *COUNT_ARG = "-c";

static void FileArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);
static void HandArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);
static void HelpArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);
static void ParsArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);
static void TestArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);
static void CountArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);


const char *CLI_ARGS[] = { "--file", "--hand", "--help", "--pars", "--test", "-c"};
static void (*Handlers[6])(CLI_FLAG*, int*, int, char**) = {&FileArgHandler, &HandArgHandler, &HelpArgHandler, &ParsArgHandler, &TestArgHandler, &CountArgHandler};

static int binSearchArg(char *targ)
{
    int beg_i = 0, end_i = 6;
    while (beg_i != end_i){
        int cur_i = (beg_i + end_i) / 2;
        int cond = strcmp(CLI_ARGS[cur_i], targ);
        if (cond < 0){
            if (beg_i == cur_i)
                break;
            beg_i = cur_i;
        }else if (cond > 0){
            end_i = cur_i;
        }else{
            return cur_i;
        }
    } 
    return -1;
}

CLI_FLAG getCliFlags(int argc, char *argv[])
{
    CLI_FLAG output = {};
    output.input_count = 1;
    for (int i = 1; i < argc; i++){
        int ind = binSearchArg(argv[i]);
        if (ind >= 0)
            Handlers[ind]( &output, &i, argc, argv);
        else
            output.main_flag = CLI_ERROR;
        if (output.main_flag == CLI_ERROR)
        {
            printf("Err");
            break;
        }
    }
    return output;
}

static void FileArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
            if(output->file_flag || output->input_type == TEST_INPUT){
                output->main_flag = CLI_ERROR;
                return;
            }
            if ((*iter)+1 >= argc){
                printf(YELLOW "You must give file name\n" DEFAULT_COLOR);
                output->main_flag = CLI_ERROR;
                return;
            }
            output->main_flag = CLI_CODE;
            if (!(output->input_type_flag)){
                output->input_type = HAND_INPUT;
            }
            output->file_flag = true;
            (*iter)++;
            output->file_name_index = *iter;
}

static void HandArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
    if(output->input_type_flag){
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = HAND_INPUT;
}

static void HelpArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
    output->main_flag = CLI_HELP;
}

static void ParsArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
    if(output->input_type_flag){
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = PARS_INPUT;
}

static void TestArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
    if(output->input_type_flag)
    {
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = TEST_INPUT;
}

static void CountArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
    if (*iter+1 < argc){
        char **endN = NULL;
        long raw_n = strtol(argv[*iter+1], endN, 10);
        if (endN == NULL || &(argv[*iter+1]) != endN){
            output->input_count = raw_n;
            (*iter)++;
        }
    }
}