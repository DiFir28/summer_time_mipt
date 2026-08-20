#include "quade.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

Quadratic initQuadratic(){
    Quadratic q = {.a = 0, .b = 0, .c = 0, .root1 = 0, .root2 = 0, .rootscount = ROOTS_ZERO};
    return q;
}

void checkQuadratic(Quadratic *q){
    assert(isfinite(q->a));
    assert(isfinite(q->b));
    assert(isfinite(q->c));

}

bool inputQuadratic(Quadratic *q){
    printf("Enter your coefficients: ");
    bool flag = (scanf("%lf %lf %lf", &(q->a), &(q->b), &(q->c)) != 3);
    if (!flag){
        checkQuadratic(q);
    }
    return flag;
}

double findDisc(Quadratic *q){
    return (q->b * q->b - (4 * q->a * q->c));
}

void solveAsLinear(Quadratic *q){
    // compare w/ 0 using eps
    if (isZero(q->b)){
        if (isZero(q->c)){
            q->rootscount = ROOTS_INF;
        }
        else{
            q->rootscount = ROOTS_ZERO;
        }
    }
    else{
        q->rootscount = ROOTS_ONE;
        q->root1 = -q->c / q->b;
    }
}

void solveQuadratic(Quadratic *q){
    if (isZero(q->a))
    {
        solveAsLinear(q);
        return;
    }
    
    double D = findDisc(q);

    if (D < 0){
        q->rootscount = ROOTS_ZERO;
    }
    else if (isZero(D)){
        q->rootscount = ROOTS_ONE;
        q->root1 = (-q->b / (2*q->a));
    }
    else{
        q->rootscount = ROOTS_TWO;
        q->root1 = (-q->b + sqrt(D)) / (2 * q->a);
        q->root2 = (-q->b - sqrt(D)) / (2 * q->a);
    }
}

void printQuadratic(Quadratic *q){
    switch (q->rootscount)
    {
    case ROOTS_INF:
        printf("Your quadratic equation has infinity roots.\n");
        break;
    case ROOTS_ZERO:
        printf("Your quadratic equation has no roots.\n");
        break;
    case ROOTS_ONE:
        printf("Your quadratic equation has 1 root. Root: %lf\n", q->root1);
        break;
    case ROOTS_TWO:
        printf("Your quadratic equation has 2 roots. Roots: %lf, %lf\n", q->root1, q->root2);
        break;    

    }
}

bool isZero(double A){
    return (abs(A) < EPSILON);
}