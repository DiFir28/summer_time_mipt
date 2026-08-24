#include "quade.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "colors.h"


// void initQuadraticEquation(QuadraticEquation *q){
//     *q = {.a = 0, .b = 0, .c = 0, .root1 = 0, .root2 = 0, .roots_count = ROOTS_ZERO};
// }

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

bool isZero(double A){
    return (fabs(A) < EPSILON);
}