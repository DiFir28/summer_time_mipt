#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "returns.h"
#include "cliprocessing.h"
#include "quade.h"
#include "colors.h"

int printInfo();
int printHelp();
int handInputHandler(QuadraticEquation *equation);
int fileInputHandler(QuadraticEquation *equation, const char *file_name);
int parsHandler(QuadraticEquation *q);
int TestHandler(QuadraticEquation *equation);

int main(int argc, const char *argv[]){
    QuadraticEquation equation;
    initQuadraticEquation(&equation);
    int script = getScript(argc, argv);

    switch (script)
    {
    case INFO:
        return printInfo();

    case HELP:
        return printHelp();

    case HAND_INPUT:        
        return handInputHandler(&equation);

    case FILE_INPUT:
        return fileInputHandler(&equation, argv[2]);

    case TESTING:
        printf("Test");
        return parsCoeffs2(&equation);
    case PARS:
        return parsHandler(&equation);
    
    default:
        return UNKNOWN_SCRIPT;
    }
}

int printInfo(){
    printf(YELLOW "Info" DEFAULT_COLOR);
    return CORRECT;
}

int printHelp(){
    printf(YELLOW "Help" DEFAULT_COLOR);
    return CORRECT;
}

int handInputHandler(QuadraticEquation *q){
    if (getInputQuadraticEquation(q)){
        printf(RED "Incorrect input.\n" DEFAULT_COLOR);
        return INCORRECT_PARAM;
    }
    solveQuadraticEquation(q);
    printRoots(q);
    return CORRECT;
}

int fileInputHandler(QuadraticEquation *q, const char *file_name){
    if (QuadraticEquationfromfile(q, file_name)){
        printf(RED "Incorrect input.\n" DEFAULT_COLOR);
        return INCORRECT_PARAM;
    }
    solveQuadraticEquation(q);
    printRoots(q);
    return CORRECT;
}

int parsHandler(QuadraticEquation *q){
    // parsCoeffs(q);
    solveQuadraticEquation(q);
    printRoots(q);
    return CORRECT;
}

QuadraticEquation tests[]={
    {4, 1, -1.3, 0.45863087, -0.70863087, ROOTS_TWO},
    {-1, 3.2, 4.7, -1.09443871, 4.29443871, ROOTS_TWO},
    {-4, 12, -9, 1.5, 0, ROOTS_ONE},
    {0, -2.6, 3.8, 1.46153846, 0, ROOTS_ONE},
    {0, 0, -6.6, 0, 0, ROOTS_ZERO},
    { 0, 0, 0, 0, 0, ROOTS_INF},
    {-6.4, 0, 4.2, -0.81009258, 0.81009258, ROOTS_TWO}
};

int TestHandler(QuadraticEquation *equation){
    for (unsigned int i = 0; i < (sizeof(tests)/sizeof(tests[0])); i++){

        initQuadraticEquation(equation);

        equation->a = tests[i].a;
        equation->b = tests[i].b;
        equation->c = tests[i].c;
        chekQuadraticEquation(equation);

        solveQuadraticEquation(equation);

        if (equation->roots_count == tests[i].roots_count){
            if (isZero(tests[i].root1 - equation->root1) && isZero(tests[i].root2 - equation->root2)){
                printf("Test %i pass\n", i+1);
            }
            else{
                printf(RED "Test %i fail  %lf %lf \n" DEFAULT_COLOR, i+1, equation->root1, equation->root2);
            }
        }
        else{
            printf(RED "Test %i fail\n" DEFAULT_COLOR, i+1);
        }
    }
    return 0;
}