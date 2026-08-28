#include "handlers.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "colors.h"
#include "returns.h"
#include "cliprocessing.h"
#include "parser.h"
#include "quade.h"


/**
 * @brief get coefficents based on CLI flag
 * @param[in] input         string for get coefficents
 * @param[in] cli_flag      parsed CLI arguments
 * @param[in, out] equation equation for write coefficents
 * @return OUTPUTS
 * @see OUTPUTS
 */
static OUTPUTS coeffsScan(char *input, CLI_FLAG *cli_flag, QuadraticEquation *equation);

/**
 * @brief print info
 */
static void printInfo();

/**
 * @brief print help
 */
static void printHelp();

OUTPUTS mainHandler(CLI_FLAG *cli_flag){
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
    printf(YELLOW_ "These programm writed in summer mipt shool by FID\n" 
                  "To see commands list enter --help\n" DEFAULT_COLOR);
}

static void printHelp()
{
    printf(YELLOW_ "============HELP===========\n"
                   "--inptut              : to enter 3 separate coefficients for ax^2 + bx + c. Enter format: 'a b c'\n"
                   "--file [filename.txt] : to read 3 separate coefficients for ax^2 + bx + c from file. Enter format in file: 'a b c'\n"
                   "--pars                : for input quadratic eqation in free format. Suported symbols: 0123456789.x+-*/^=\n"
                   "--test                : for run prepared tests" DEFAULT_COLOR);
}

OUTPUTS codeHandler(CLI_FLAG *cli_flag, char *argv[], QuadraticEquation *q)
{
    char input[MAX_INPUT_SIZE] = {};
    input[0] = '+';
    QuadraticEquation equation = {};
    if ((cli_flag->input_type == CODE_TEST)){
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
            if(fgets(input+1, MAX_INPUT_SIZE, file) == NULL)
                return FILE_ERROR;
        }else{
            printf(GREEN_ "Your input:" DEFAULT_COLOR);
            if(fgets(input+1, MAX_INPUT_SIZE, stdin) == NULL)
                return INCORRECT_PARAM;
        }
        OUTPUTS scan_out = coeffsScan(input, cli_flag, &equation); 
        if (scan_out != CORRECT){
            return scan_out;
        }
        checkQuadraticEquation(&equation);
        solveQuadraticEquation(&equation);
        printRoots(&equation);
        *q = equation;
    }
    if(cli_flag->file_flag){
        fclose(file);
    }
    return CORRECT;
}

/**
 * @brief complite 8 prepared tests
 */
static void preparedTestsHandler(){
    QuadraticEquation hand_input_tests[] = {
    {    4,        1,   -1.3,  0.45863087, -0.70863087,  ROOTS_TWO},
    {   -1,      3.2,    4.7, -1.09443871,  4.29443871,  ROOTS_TWO},
    {   -4,       12,     -9,         1.5,           0,  ROOTS_ONE},
    {    0,     -2.6,    3.8,  1.46153846,           0,  ROOTS_ONE},
    {    0,        0,   -6.6,           0,           0, ROOTS_ZERO},
    {    0,        0,      0,           0,           0,  ROOTS_INF},
    { -6.4,        0,    4.2, -0.81009258,  0.81009258,  ROOTS_TWO},
    {7.209, -265.868, 2429.6, 20.17512489, 16.70488620,  ROOTS_TWO}};

    QuadraticEquation equation = {};
    unsigned passed_cnt =0;
    for (unsigned int i = 0, n = (sizeof(hand_input_tests)/sizeof(hand_input_tests[0])); i < n; i++){
        equation = {};
        equation.a = hand_input_tests[i].a;
        equation.b = hand_input_tests[i].b;
        equation.c = hand_input_tests[i].c;
        checkQuadraticEquation(&equation);
        solveQuadraticEquation(&equation);
        if (equation.roots_count == hand_input_tests[i].roots_count){
            if ((isZero(hand_input_tests[i].root1 - equation.root1) && isZero(hand_input_tests[i].root2 - equation.root2)) 
            || (isZero(hand_input_tests[i].root1 - equation.root2) && isZero(hand_input_tests[i].root2 - equation.root1))){
                passed_cnt++;
            }
            else{
                printf(RED_ "Test %i fail  %lf %lf \n" DEFAULT_COLOR, i+1, equation.root1, equation.root2);
            }
        }
        else{
            printf(RED_ "Test %i fail\n" DEFAULT_COLOR, i+1);
        }
    }
    printf("Passed prepared tests %i/%lli tests\n", passed_cnt, (sizeof(hand_input_tests)/sizeof(hand_input_tests[0])));
}

/**
 * @brief complite N random tests
 * @param[in] cnt_tests how many random tests will be complite
 */
static void randTestHandler(const unsigned cnt_tests){
    QuadraticEquation equation = {};
    srand(time(NULL));
    unsigned passed_rand_cnt = 0;
    for (unsigned i = 0; i < cnt_tests; i++){
        
        checkQuadraticEquation(&equation);
        solveQuadraticEquation(&equation);
        if (!checkQuadraticEquationRoots(&equation)){
            printf(RED_ "Test with %lg %lg %lg fail  %lf %lf \n" DEFAULT_COLOR, equation.a,  equation.b, equation.c, equation.root1, equation.root2);
        }else{
            passed_rand_cnt++;
        }
    }
    printf("Passed random tests %u/%u tests\n", passed_rand_cnt, cnt_tests);
}

/**
 * @brief complite N random tests
 * @param[in] cnt_tests     how many random tests will be complite
 * @param[in] cnt_summand   max number of summand that will be generated
 */
static void parseTest(unsigned cnt_tests, unsigned cnt_summand){
    cnt_summand--;
    unsigned pass_cnt = 0;
    srand(time(NULL));
    for (unsigned j = 0; j < cnt_tests; j++){
        char input[MAX_INPUT_SIZE] = {0};
        double generat_coeffs[3] = {};
        int Ind = 0;
        unsigned summand_cnt = rand()%cnt_summand+1;
        for (unsigned i = 0; i < summand_cnt; i++){
            double cur_coeff = (rand()%100000)/1000.0; // make call function
            bool sign = rand()%2;
            if (sign){
                input[Ind] = '+';
            }else{
                input[Ind] = '-';
            }
            Ind++;
            Ind+= sprintf(input+Ind, "%.3f", cur_coeff);
            
            unsigned x_pow = rand()%3;
            if (rand()%2 && x_pow != 0){
                input[Ind++] = '*';
            }
            if (x_pow == 2){            
                unsigned write_type = rand()%2;
                if(write_type){
                    strcat(input, "x^2");
                    Ind+=3;
                }else{
                    strcat(input, "x*x");
                    Ind+=3;
                }
            }else if(x_pow == 1){
                input[Ind] = 'x';
                Ind+=1;
            }

            if (sign){
                generat_coeffs[x_pow] += cur_coeff;
            }else{
                generat_coeffs[x_pow] -= cur_coeff;
            }
        }
        
        double parse_coeffs[3] = {};
        if (parseCoeffs(input, parse_coeffs)){
                printf(RED_ "Wrong generate" DEFAULT_COLOR);
        }
        if (!(isZero(generat_coeffs[2] - parse_coeffs[2]) && isZero(generat_coeffs[1] - parse_coeffs[1]) && isZero(generat_coeffs[0] - parse_coeffs[0]))){
            printf(RED_ "%s\n" DEFAULT_COLOR,input);
            printf("Expected: %lg %lg %lg", generat_coeffs[2], generat_coeffs[1], generat_coeffs[0]);
            printf("Gived: %lg %lg %lg", parse_coeffs[2], parse_coeffs[1], parse_coeffs[0]);
        }else{
            printf(GREEN_ "%s\n" DEFAULT_COLOR,input);
            pass_cnt++;
        }
    }
    printf("Passed parse tests %u/%u tests\n", pass_cnt, cnt_tests);
}

OUTPUTS TestHandler()
{
    preparedTestsHandler();
    randTestHandler(100);
    parseTest(20, 10);
    return CORRECT;
}

static OUTPUTS coeffsScan(char *input, CLI_FLAG *cli_flag, QuadraticEquation *equation)
{
    if (cli_flag->input_type == SEP_INPUT){
        // printf("%s", input);
            if (sscanf(input+1, "%lf%*[ ]%lf%*[ ]%lf %s", &(equation->a), &(equation->b), &(equation->c), input) != 3){
            return INCORRECT_PARAM;
            if (input[0] != '\0')
            return INCORRECT_PARAM;
        }
        checkQuadraticEquation(equation);
    }else{
        double x_coeffs[3] = {0};
        if (parseCoeffs(input, x_coeffs)){
            return INCORRECT_PARAM;
        }
        printf("Result coefs: %lg %lg %lg\n", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
        equation->a = x_coeffs[2];
        equation->b = x_coeffs[1];
        equation->c = x_coeffs[0];
    }
    return CORRECT;
}