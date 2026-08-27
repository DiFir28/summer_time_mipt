#ifndef __QUADE__
#define __QUADE__

/** 
 * @file quade.h
 * @brief File contains struct of quadratic equation, enum for count of roots, and main functions for solving quadratic equations
 */

#include <stdbool.h>

#define EPSILON 1e-7

/**
 * @brief macross for asserts, that added call information (which file, wich line)
 */
#define checkLink(x); checkLinkSys(x, __FILE__, __LINE__);
#define checkQuadraticEquation(x); checkQuadraticEquationSys(x, __FILE__, __LINE__);

/**
 * @brief Enum for count how many roots have quadratic equation
 */
typedef enum{
    ROOTS_ZERO = 0, /**< zero roots */
    ROOTS_ONE = 1,  /**< only one root */
    ROOTS_TWO = 2,  /**< two roots*/
    ROOTS_INF = -1  /**< infinity roots */
} ROOTSCOUNT;

/**
 * @brief Struct of quadratic equation 
 * @see ROOTSCOUNT
 */
typedef struct {
    double a, b, c;         /**< coefficents */
    double root1, root2;    /**< roots */
    ROOTSCOUNT roots_count; /**< count of roots*/
} QuadraticEquation;

/**
 * @brief Compare double with zero using EPSILON
 * @param[in] num number for compare
 * @return bool
 * @retval true     number coloser to zero than EPSILON
 * @retval false    number farther to zero than EPSILON
 */
bool isZero(double num);

/**
 * @brief check is pointer  set on NULL (if yes abort)
 * @param[in] q     pointer to check
 * @param[in] file  from which file function call
 * @param[in] line  from which line function call
 */
void checkLinkSys(QuadraticEquation *q, const char* file, unsigned line);

/**
 * @brief check coefficents off quadratic equation (NaN or Inf) (if yes abort)
 * @param[in] q     quadratic equation to check
 * @param[in] file  from which file function call
 * @param[in] line  from which line function call
 */
void checkQuadraticEquationSys(QuadraticEquation *q, const char* file, unsigned line);

/**
 * @brief Calc discriminant of quadratic eqation
 * @param[in] q     quadratic eqation for which will be calc discriminant
 * @return double   discriminant
 */
double calcDiscriminant(QuadraticEquation *q);

/**
 * @brief Solve qadratic eqation
 * @param[in, out] q    quadratic eqation for which will be solve, and in which roots are written
 */
void solveQuadraticEquation(QuadraticEquation *q);

/**
 * @brief Calc value of quadratic eqation in point X
 * @param[in] q quadratic eqation
 * @param[in] x the x for value
 * @return double Value in point X
 */
double calcValQuadraticEquation(QuadraticEquation *q, double x);

/**
 * @brief Print roots of qadratic eqation
 * @param[in] q     quadratic eqation, which roots will be print
 */
void printRoots(QuadraticEquation *q);

/**
 * @brief check is roots of qadratic eqation give 0
 * @param[in] q     quadratic eqation, which roots will be check
 */
bool checkQuadraticEquationRoots(QuadraticEquation *q);

/**
 * @brief generate random coefficents
 * @param[in] q     quadratic eqation, which coefficents will be generate
 */
void randQuadraticEquation(QuadraticEquation *q);

#endif