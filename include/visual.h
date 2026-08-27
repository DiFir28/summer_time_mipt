#ifndef __VISUAL__
#define __VISUAL__

#include "raylib.h"
#include "quade.h"

#define WINDOWS_SIZE 1000

/**
 * @brief Init window and set frame rate
 */
void visualInit();

/**
 * @brief Draw Axis and Grid based on offset 
 */
void drawMainGrid(Vector2 axis_offset);

/**
 * @brief Draw quadratic equation based on offset
 */
void drawQadraticEquation( QuadraticEquation *q, Vector2 offset);

/**
 * @brief change offset and scale based on mouse moving
 */
void mouseHandler(Vector2 *offset);

/**
 * @brief main visual loop, processing mouse input and draw qadratic equation and grid
 */
void visualLoop(QuadraticEquation *q);

#endif