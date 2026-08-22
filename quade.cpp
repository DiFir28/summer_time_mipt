#include "quade.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "colors.h"


void initQuadraticEquation(QuadraticEquation *q){
    *q = {.a = 0, .b = 0, .c = 0, .root1 = 0, .root2 = 0, .roots_count = ROOTS_ZERO};
}

void checkLinkS(QuadraticEquation *q, const char* file, unsigned line){
    if ((q==NULL)){
        printf(RED "Incorrect Link, file %s line %d.\n" DEFAULT_COLOR, file, line);
        abort();
    }
}

void chekQuadraticEquationS(QuadraticEquation *q, const char* file, unsigned line){
    checkLink(q);
    if (!(isfinite(q->a) && isfinite(q->b) && isfinite(q->c))){
        printf(RED "Incorrect coefficients, file %s line %d.\n" DEFAULT_COLOR, file, line);
        abort();
    }
}

bool getInputQuadraticEquation(QuadraticEquation *q){
    checkLink(q);
    bool completed_flag = false;
    printf(GREEN "Enter your coefficients: " DEFAULT_COLOR);
    do{
        completed_flag = (scanf("%lf%*[ ]%lf%*[ ]%lf", &(q->a), &(q->b), &(q->c)) != 3);
        if (!completed_flag){
            chekQuadraticEquation(q);
        }
        while (getchar() != '\n'){
            completed_flag = true;
        }
        if (completed_flag == true){
            printf(YELLOW "Wrong coefficients, try again: " DEFAULT_COLOR);
        }
    }while (completed_flag);

    return completed_flag;
}

bool QuadraticEquationfromfile(QuadraticEquation *q, const char *file_name){
    checkLink(q);
    FILE *file = fopen(file_name, "r");
    if (file == NULL){// errno
        printf(RED "Incorrect file" DEFAULT_COLOR);
        return true;
    }
    int count_flag = fscanf(file,"%lf %lf %lf", &(q->a), &(q->b), &(q->c));
    if (count_flag != 3){
        printf(RED "Incorrect file" DEFAULT_COLOR);
        return true;
    }
    fclose(file);
    chekQuadraticEquation(q);
    return false;
}

double findDiscriminant(QuadraticEquation *q){
    checkLink(q);
    return (q->b * q->b - (4 * q->a * q->c));
}

static void solveAsLinear(QuadraticEquation *q){
    checkLink(q);
    if (isZero(q->b)){
        if (isZero(q->c)){
            q->roots_count = ROOTS_INF;
        }
        else{
            q->roots_count = ROOTS_ZERO;
        }
    }
    else{
        q->roots_count = ROOTS_ONE;
        q->root1 = -q->c / q->b;

        if (isZero(q->root1)){
            q->root1 = 0;
        }
    }
}

static void solveAsQuadraticEquation(QuadraticEquation *q){  
    checkLink(q);
    double D = findDiscriminant(q);

    if (D < 0){
        q->roots_count = ROOTS_ZERO;
    }
    else if (isZero(D)){
        q->roots_count = ROOTS_ONE;
        q->root1 = (-q->b / (2*q->a));

        if (isZero(q->root1)){
            q->root1 = 0;
        }
    }
    else{
        q->roots_count = ROOTS_TWO;
        double sqrtD = sqrt(D);
        q->root1 = (-q->b + sqrtD) / (2 * q->a);
        q->root2 = (-q->b - sqrtD) / (2 * q->a);

        if (isZero(q->root1)){
            q->root1 = 0;
        }
        if (isZero(q->root2)){
            q->root2 = 0;
        }
    }
}

void solveQuadraticEquation(QuadraticEquation *q){
    checkLink(q);
    if (isZero(q->a))
    {
        solveAsLinear(q);
        return;
    }
    solveAsQuadraticEquation(q);
}

void printRoots(QuadraticEquation *q){
    checkLink(q);
    switch (q->roots_count)
    {
    case ROOTS_INF:
        printf(GREEN "Your quadratic equation has infinity roots.\n" DEFAULT_COLOR);
        break;
    case ROOTS_ZERO:
        printf(GREEN "Your quadratic equation has no roots.\n" DEFAULT_COLOR);
        break;
    case ROOTS_ONE:
        printf(GREEN "Your quadratic equation has 1 root. Root: %lg\n" DEFAULT_COLOR, q->root1);
        break;
    case ROOTS_TWO:
        printf(GREEN "Your quadratic equation has 2 roots. Roots: %lg, %lg\n" DEFAULT_COLOR, q->root1, q->root2);
        break;    

    }
}

// bool parsCoeffs(QuadraticEquation *q){
//     checkLink(q);
//     bool completed_flag = false;
//     printf(GREEN "Enter your equation in format ax^2+bx+c: " DEFAULT_COLOR);
//     char INPUT[50];
//     unsigned x_offsets[2];
//     unsigned x_count = 0;
//     scanf("%[^\n]", INPUT);
//     char *clearInput  = (char*)malloc(strlen(INPUT)); // todo: malloc abuse
//     // ! remane
//     unsigned J =0;
//     for(unsigned I = 0; I <= unsigned(strlen(INPUT)); I++){
//         if ((INPUT[I] == ' ') ||(INPUT[I] == '*')){
//             continue;
//         }
//         if (INPUT[I] == '^'){
//             I++;
//             continue;
//         }
//         if (INPUT[I] == 'x'){
//             clearInput[J] = '\0';
//             x_offsets[x_count] = J;
//             x_count+=1;
//             J++;
//             continue;
//         }
//         clearInput[J] = INPUT[I];
//         J++;
        
//     }
//     clearInput[J] = '\0';

//     if (clearInput[0] == '\0' || (clearInput[1] == '\0' && (clearInput)[0] == '+')){
//         q->a = 1;
//     }else if((clearInput)[0] == '-'  &&  clearInput[1] == '\0'){
//         q->a = -1;
//     }else{
//         sscanf(clearInput, "%lf", &(q->a));
//     }

//     if ((clearInput + beg_offset + 1)[1] == '\0' && (clearInput + beg_offset + 1)[0] == '+'){
//         q->b = 1;
//     }else if((clearInput + beg_offset + 1)[1] == '\0' && (clearInput + beg_offset + 1)[0] == '-'){
//         q->b = -1;
//     }else{
//         sscanf(clearInput + beg_offset + 1, "%lf", &(q->b));
//     }

//     if ((clearInput + end_offset + 1)[0] != '\0' && (clearInput + end_offset + 1)[1] != '\0'){
//         sscanf(clearInput + end_offset + 1, "%lf", &(q->c));
//     }else{
//         (q->c) = 0;
//     } //TODO copy pasta
//     return completed_flag;
    
    
// }

bool parsCoeffs2(QuadraticEquation *q){
    checkLink(q);
    bool completed_flag = false;    
    char INPUT[254];
    double x_coeffs[3] = {0}; //! index ~ power of x
    unsigned beg_offset = 0, end_offset = 0;

    printf(GREEN "Enter your equation in format ax^2+bx+c: " DEFAULT_COLOR);
    scanf("%[^\n]", INPUT);

    unsigned J =0;
    for(unsigned I = 0; I <= unsigned(strlen(INPUT)); I++){
        if ((INPUT[I] == ' ') || (INPUT[I] == '*') || (INPUT[I] == '^')){
            continue;
        }
        if (J == 0 && INPUT[I] == 'x'){
            INPUT[J] = '+';
            J++;
        }
        INPUT[J] = INPUT[I];
        J++;
    }    
    
    for(unsigned I = 0, n = unsigned(strlen(INPUT)); I <= n; I++){
        char buff[32] = {0};
        if (INPUT[I] != '+' && INPUT[I] != '-' && INPUT[I] != '\0'){
            continue;
        }
        beg_offset = end_offset;
        end_offset = I;
        double k = 0; 
        strncpy(buff, INPUT + beg_offset, end_offset - beg_offset);

        char xbuff[32] = {0};
        char kbuff[32] = {0};
        sscanf(buff, "%[^x\n]%s", kbuff, xbuff); //TODO strchr
        if (strlen(kbuff) == 0){
            continue;
        }else if(strlen(kbuff) == 1 && (kbuff)[0] == '+'){
            k = 1;
        }else if(strlen(kbuff) == 1 && (kbuff)[0] == '-'){
            k = -1; // TODO: rename single letter variables
        }else{        
            k = atof(kbuff);
        }
        if (xbuff[0] == ' '){
            x_coeffs[0]+=k;
        }else if(strlen(xbuff) == 1){
            x_coeffs[1]+=k;
        }else{
            x_coeffs[atoi(xbuff+1)]+=k;
        }        
    }

    printf("%lg %lg %lg", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
    return completed_flag;
}

bool isZero(double A){
    return (fabs(A) < EPSILON);
}