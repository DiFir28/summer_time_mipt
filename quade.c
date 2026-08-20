#include "quade.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "colors.h"

void initQuadraticEquation(QuadraticEquation *q){
    *q = {.a = 0, .b = 0, .c = 0, .root1 = 0, .root2 = 0, .roots_count = ROOTS_ZERO};
}

void chekQuadraticEquation(QuadraticEquation *q){
    assert(isfinite(q->a));
    assert(isfinite(q->b));
    assert(isfinite(q->c));
}

bool getInputQuadraticEquation(QuadraticEquation *q){
    bool flag = 2;
    printf(GREEN "Enter your coefficients: " DEFOULT_COLOR);
    while (flag != 0){
        
        flag = (scanf("%lf %lf %lf", &(q->a), &(q->b), &(q->c)) != 3);
        if (!flag){
            chekQuadraticEquation(q);
        }
        while (getchar() != '\n'){
            flag = 1;
        }
        if (flag == 1){
            printf(YELLOW "Wrong coefficients, try again: " DEFOULT_COLOR);
        }
    }
    return flag;
}

bool QuadraticEquationfromfile(QuadraticEquation *q, char *file_name){
    FILE *file = fopen(file_name, "r");
    if (file == NULL){// errno
        printf(RED "Incorrect file" DEFOULT_COLOR);
        return 1;
    }
    int count_flag = fscanf(file,"%lf %lf %lf", &(q->a), &(q->b), &(q->c));
    if (count_flag != 3){
        printf(RED "Incorrect file" DEFOULT_COLOR);
        return 1;
    }
    fclose(file);
    chekQuadraticEquation(q);
    return 0;
}

double findDisc(QuadraticEquation *q){
    return (q->b * q->b - (4 * q->a * q->c));
}

void solveAsLinear(QuadraticEquation *q){
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

void solveAsQuadraticEquation(QuadraticEquation *q){  
    double D = findDisc(q);

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
        q->root1 = (-q->b + sqrt(D)) / (2 * q->a);
        q->root2 = (-q->b - sqrt(D)) / (2 * q->a);

        if (isZero(q->root1)){
            q->root1 = 0;
        }
        if (isZero(q->root2)){
            q->root2 = 0;
        }
    }
}

void solveQuadraticEquation(QuadraticEquation *q){
    if (isZero(q->a))
    {
        solveAsLinear(q);
        return;
    }
    solveAsQuadraticEquation(q);
}

void printRoots(QuadraticEquation *q){
    switch (q->roots_count)
    {
    case ROOTS_INF:
        printf(GREEN "Your quadratic equation has infinity roots.\n" DEFOULT_COLOR);
        break;
    case ROOTS_ZERO:
        printf(GREEN "Your quadratic equation has no roots.\n" DEFOULT_COLOR);
        break;
    case ROOTS_ONE:
        printf(GREEN "Your quadratic equation has 1 root. Root: %lf\n" DEFOULT_COLOR, q->root1);
        break;
    case ROOTS_TWO:
        printf(GREEN "Your quadratic equation has 2 roots. Roots: %lf, %lf\n" DEFOULT_COLOR, q->root1, q->root2);
        break;    

    }
}

bool isZero(double A){
    return (abs(A) < EPSILON);
}