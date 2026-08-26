#include "handlers.h"

#include <stdio.h>
#include "colors.h"
#include "returns.h"
#include "cliprocessing.h"
#include "parser.h"
#include "quade.h"

static OUTPUTS coeffsScan(char *input, CLI_FLAG *cli_flag, QuadraticEquation *equation);
static void printInfo();
static void printHelp();

OUTPUTS mainHandler(CLI_FLAG *cli_flag, char *argv[]){
    switch (cli_flag->main_flag)
    {
    case CLI_INFO:
        printInfo();
        return CORRECT;
    case CLI_HELP:
        printHelp();
        return CORRECT;
    case CLI_CODE:
        return MAIN_CODE;
    case CLI_ERROR:        
        return UNKNOWN_CLI_FLAGS;        
    }
    return CORRECT;    
}

static void printInfo()
{
    printf(YELLOW "These programm writed in summer mipt shool by FID\n" 
                  "To see commands list enter --help\n" DEFAULT_COLOR);
}

static void printHelp()
{
    printf(YELLOW "============HELP===========\n"
                   "--inptut              : to enter 3 separate coefficients for ax^2 + bx + c. Enter format: 'a b c'\n"
                   "--file [filename.txt] : to read 3 separate coefficients for ax^2 + bx + c from file. Enter format in file: 'a b c'\n"
                   "--pars                : for input quadratic eqation in free format. Suported symbols: 0123456789.x+-*/^=\n"
                   "--test                : for run prepared tests" DEFAULT_COLOR);
}

OUTPUTS codeHandler(CLI_FLAG *cli_flag, char *argv[])
{
    char input[MAX_INPUT_SIZE] = {0};
    QuadraticEquation equation = {};
    if ((cli_flag->input_type == TEST_INPUT)){
        return TestHandler();
    }
    FILE *file;
    if(cli_flag->file_flag){
        file  = fopen(argv[cli_flag->file_name_index], "r");
        if (file == NULL){
            return FILE_ERROR;
        }
    }
    for (unsigned i = 0; i < cli_flag->input_count; i++){
        if (cli_flag->file_flag){  
            if(fgets(input, MAX_INPUT_SIZE, file) == NULL)
                return FILE_ERROR;
        }else{
            printf(GREEN "Your input:" DEFAULT_COLOR);
            if(fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
                return INCORRECT_PARAM;
        }
        OUTPUTS scan_out = coeffsScan(input, cli_flag, &equation); 
        if (scan_out != CORRECT){
            return scan_out;
        }
        solveQuadraticEquation(&equation);
        printRoots(&equation);
    }
    if(cli_flag->file_flag){
        fclose(file);
    }
    return CORRECT;

}

QuadraticEquation hand_input_tests[] = {
    {    4,        1,   -1.3,  0.45863087, -0.70863087,  ROOTS_TWO},
    {   -1,      3.2,    4.7, -1.09443871,  4.29443871,  ROOTS_TWO},
    {   -4,       12,     -9,         1.5,           0,  ROOTS_ONE},
    {    0,     -2.6,    3.8,  1.46153846,           0,  ROOTS_ONE},
    {    0,        0,   -6.6,           0,           0, ROOTS_ZERO},
    {    0,        0,      0,           0,           0,  ROOTS_INF},
    { -6.4,        0,    4.2, -0.81009258,  0.81009258,  ROOTS_TWO},
    {7.209, -265.868, 2429.6, 20.17512489, 16.70488620,  ROOTS_TWO}};


OUTPUTS TestHandler()
{
    QuadraticEquation equation = {};
    unsigned passed_cnt =0;
    for (unsigned int i = 0, n = (sizeof(hand_input_tests)/sizeof(hand_input_tests[0])); i < n; i++){
        equation = {};
        equation.a = hand_input_tests[i].a;
        equation.b = hand_input_tests[i].b;
        equation.c = hand_input_tests[i].c;
        chekQuadraticEquation(&equation);
        solveQuadraticEquation(&equation);
        if (equation.roots_count == hand_input_tests[i].roots_count){
            if ((isZero(hand_input_tests[i].root1 - equation.root1) && isZero(hand_input_tests[i].root2 - equation.root2)) 
            || (isZero(hand_input_tests[i].root1 - equation.root2) && isZero(hand_input_tests[i].root2 - equation.root1))){
                passed_cnt++;
            }
            else{
                printf(RED "Test %i fail  %lf %lf \n" DEFAULT_COLOR, i+1, equation.root1, equation.root2);
            }
        }
        else{
            printf(RED "Test %i fail\n" DEFAULT_COLOR, i+1);
        }
    }
    printf("Passed %i/%lli tests", passed_cnt, (sizeof(hand_input_tests)/sizeof(hand_input_tests[0])));
    return CORRECT;
}

static OUTPUTS coeffsScan(char *input, CLI_FLAG *cli_flag, QuadraticEquation *equation)
{
    if (cli_flag->input_type == HAND_INPUT){
        // printf("%s", input);
            if (sscanf(input, "%lf%*[ ]%lf%*[ ]%lf", &(equation->a), &(equation->b), &(equation->c)) != 3){
            return INCORRECT_PARAM;
        }
        chekQuadraticEquation(equation);
    }else{
        double x_coeffs[3] = {0};
        if (parsCoeffs(x_coeffs, input)){
            return INCORRECT_PARAM;
        }
        printf("Result coefs: %lg %lg %lg\n", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
        equation->a = x_coeffs[0];
        equation->b = x_coeffs[1];
        equation->c = x_coeffs[2];
    }
    return CORRECT;
}