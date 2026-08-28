#include "quade.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "colors.h"


void checkLinkSys(QuadraticEquation *q, const char* file, unsigned line)
{
    if ((q==NULL))
    {
        printf(RED_ "Incorrect Link, file %s line %d.\n" DEFAULT_COLOR, file, line);
        abort();
    }
}

void checkQuadraticEquationSys(QuadraticEquation *q, const char* file, unsigned line)
{
    checkLink(q);
    if (!(isfinite(q->a) && isfinite(q->b) && isfinite(q->c)))
    {
        printf(RED_ "Incorrect coefficients, file %s line %d.\n" DEFAULT_COLOR, file, line);
        abort();
    }
}

double calcDiscriminant(QuadraticEquation *q)
{
    checkLink(q);
    return (q->b * q->b - (4 * q->a * q->c));
}

/**
 * @brief Solve linear equation
 * @param[in, out] q equation for solve
 */
static void solveAsLinearEquation(QuadraticEquation *q)
{
    checkLink(q);
    if (isZero(q->b))
    {
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


/**
 * @brief Solve quadratic equation
 * @param[in, out] q equation for solve
 */
static void solveAsQuadraticEquation(QuadraticEquation *q)
{  
    checkLink(q);
    double D = calcDiscriminant(q);

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

void solveQuadraticEquation(QuadraticEquation *q)
{
    checkLink(q);
    if (isZero(q->a))
    {
        solveAsLinearEquation(q);
        return;
    }
    solveAsQuadraticEquation(q);
}

double calcValQuadraticEquation(QuadraticEquation *q, double x){
    return (q->a * x * x + q->b * x + q->c);
}

void printRoots(QuadraticEquation *q)
{
    checkLink(q);
    switch (q->roots_count)
    {
    case ROOTS_INF:
        printf(GREEN_ "Your quadratic equation has infinity roots.\n" DEFAULT_COLOR);
        break;
    case ROOTS_ZERO:
        printf(GREEN_ "Your quadratic equation has no roots.\n" DEFAULT_COLOR);
        break;
    case ROOTS_ONE:
        printf(GREEN_ "Your quadratic equation has 1 root. Root: %lg\n" DEFAULT_COLOR, q->root1);
        break;
    case ROOTS_TWO:
        printf(GREEN_ "Your quadratic equation has 2 roots. Roots: %lg, %lg\n" DEFAULT_COLOR, q->root1, q->root2);
        break;    

    }
}

bool checkQuadraticEquationRoots(QuadraticEquation *q){
    checkLink(q);
    switch (q->roots_count)
    {
    case ROOTS_INF:
        return true;
    case ROOTS_ZERO:
        return (calcDiscriminant(q) < 0);
    case ROOTS_ONE:
        return isZero(calcValQuadraticEquation(q, q->root1));
    case ROOTS_TWO:
        return ( isZero(calcValQuadraticEquation(q, q->root1)) && isZero(calcValQuadraticEquation(q, q->root2)));
    }
    return false;
}

void randQuadraticEquation(QuadraticEquation *q){
    q = {};
    q->a = (rand()%1000000 - 500000)/1000.0;
    q->b = (rand()%1000000 - 500000)/1000.0;
    q->c = (rand()%1000000 - 500000)/1000.0;
}

bool isZero(double num)
{
    return (fabs(num) < EPSILON);
}