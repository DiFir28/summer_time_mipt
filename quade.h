#ifndef __QUADE__
#define __QUADE__

#include <stdbool.h>

#define EPSILON 1e-7

typedef enum{
    // ROOT_NEGATIVE_DISC = 0,
    // ROOT_ZERO_DISC = 1,
    // ROOT_POSITIVE_DISC = 2,
    // ROOT_INFINITY = -1
    ROOTS_ZERO = 0,
    ROOTS_ONE = 1,
    ROOTS_TWO = 2,
    ROOTS_INF = -1
} ROOTSCOUNT;

typedef struct {
    double a, b, c, root1, root2;
    ROOTSCOUNT rootscount;
} Quadratic;

bool isZero(double A);

Quadratic initQuadratic();
void checkQuadratic(Quadratic *q);
bool inputQuadratic(Quadratic *q);
double findDisc(Quadratic *q);
void solveAsLinear(Quadratic *q);
void solveQuadratic(Quadratic *q);
void printQuadratic(Quadratic *q);

#endif