#ifndef __QUADE__
#define __QUADE__

#include <stdbool.h>

#define EPSILON 1e-7

typedef enum{
    ROOTS_ZERO = 0,
    ROOTS_ONE = 1,
    ROOTS_TWO = 2,
    ROOTS_INF = -1
} ROOTSCOUNT;

typedef struct {
    double a, b, c, root1, root2;
    ROOTSCOUNT roots_count;
} QuadraticEquation;

bool isZero(double A);

void initQuadraticEquation(QuadraticEquation *q);
void chekQuadraticEquation(QuadraticEquation *q);
bool getInputQuadraticEquation(QuadraticEquation *q);
bool QuadraticEquationfromfile(QuadraticEquation *q, char* file);
double findDisc(QuadraticEquation *q);
void solveAsLinear(QuadraticEquation *q);
void solveQuadraticEquation(QuadraticEquation *q);
void printRoots(QuadraticEquation *q);

#endif