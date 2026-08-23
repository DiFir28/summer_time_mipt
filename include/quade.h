#ifndef __QUADE__
#define __QUADE__

#include <stdbool.h>

#define EPSILON 1e-7
#define checkLink(x); checkLinkS(x, __FILE__, __LINE__);
#define chekQuadraticEquation(x); chekQuadraticEquationS(x, __FILE__, __LINE__);

typedef enum{
    ROOTS_ZERO = 0,
    ROOTS_ONE = 1,
    ROOTS_TWO = 2,
    ROOTS_INF = -1
} ROOTSCOUNT;

typedef struct {
    double a, b, c;
    double root1, root2;
    ROOTSCOUNT roots_count;
} QuadraticEquation;

bool isZero(double A);

void checkLinkS(QuadraticEquation *q, const char* file, unsigned line);
void chekQuadraticEquationS(QuadraticEquation *q, const char* file, unsigned line);
void initQuadraticEquation(QuadraticEquation *q);
bool getInputQuadraticEquation(QuadraticEquation *q);
bool QuadraticEquationfromfile(QuadraticEquation *q, const char* file);
double findDiscriminant(QuadraticEquation *q);
void solveQuadraticEquation(QuadraticEquation *q);
void printRoots(QuadraticEquation *q);


#endif