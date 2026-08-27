#include "cliprocessing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

/**
 * @brief handle file arg
 * @param[in, out] output CLI output struct
 * @param[in] iter index of "--file" cli arg
 * @param[in] argc arg count
 * @param[in] argv args
 */
static void FileArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);

/**
 * @brief handle separate input cli arg
 * @param[in, out] output CLI output struct
 */
static void SepArgHandler(CLI_FLAG *output, int*, int, char**);

/**
 * @brief handle help input arg
 * @param[in, out] output CLI output struct
 */
static void HelpArgHandler(CLI_FLAG *output, int*, int, char**);

/**
 * @brief handle parse input arg
 * @param[in, out] output CLI output struct
 */
static void ParsArgHandler(CLI_FLAG *output, int*, int, char**);

/**
 * @brief handle test arg
 * @param[in, out] output CLI output struct
 */
static void TestArgHandler(CLI_FLAG *output, int*, int, char**);


/**
 * @brief handle visual arg
 * @param[in, out] output CLI output struct
 */
static void VisArgHandler(CLI_FLAG *output, int*, int, char**);

/**
 * @brief handle file arg
 * @param[in, out] output CLI output struct
 * @param[in] iter index of "--file" cli arg
 * @param[in] argc arg count
 * @param[in] argv args
 */
static void CountArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[]);

//? What do you think about making array of structs
const char *CLI_ARGS[] = { "--file", "--hand", "--help", "--pars", "--test", "--vis", "-c"};
static void (*Handlers[7])(CLI_FLAG*, int*, int, char**) = {&FileArgHandler, &SepArgHandler, &HelpArgHandler, &ParsArgHandler, &TestArgHandler, &VisArgHandler, &CountArgHandler};

/**
 * @brief search index of cli arg
 * @param[in] targ target cli arg
 * @return index of targ (if -1 is not a cli arg)
 */
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
            break;
    }
    return output;
}

static void FileArgHandler(CLI_FLAG *output, int *iter, int argc, char *argv[])
{
            if(output->file_flag || output->input_type == CODE_TEST){
                output->main_flag = CLI_ERROR;
                return;
            }
            if ((*iter)+1 >= argc){
                printf(YELLOW_ "You must give file name\n" DEFAULT_COLOR);
                output->main_flag = CLI_ERROR;
                return;
            }
            output->main_flag = CLI_CODE;
            if (!(output->input_type_flag)){
                output->input_type = SEP_INPUT;
            }
            output->file_flag = true;
            (*iter)++;
            output->file_name_index = *iter;
}

static void SepArgHandler(CLI_FLAG *output, int*, int, char**)
{
    if(output->input_type_flag){
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = SEP_INPUT;
}

static void HelpArgHandler(CLI_FLAG *output, int*, int, char**)
{
    output->main_flag = CLI_HELP;
}

static void ParsArgHandler(CLI_FLAG *output, int*, int, char**)
{
    if(output->input_type_flag){
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = PARS_INPUT;
}

static void TestArgHandler(CLI_FLAG *output, int*, int, char**)
{
    if(output->input_type_flag || output->visual_flag)
    {
        output->main_flag = CLI_ERROR;
        return;
    }
    output->input_type_flag = true;
    output->main_flag = CLI_CODE;
    output->input_type = CODE_TEST;
}

static void VisArgHandler(CLI_FLAG *output, int*, int, char**){
    if (output->input_type == CODE_TEST){
        output->main_flag = CLI_ERROR;
        return;
    }
    output->visual_flag = true;
    output->main_flag = CLI_CODE;
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