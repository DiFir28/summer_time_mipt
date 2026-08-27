#ifndef __VISUAL__
#define __VISUAL__

#include "raylib.h"
#include "quade.h"

#define WINDOWS_SIZE 1000

/**
 * @brief struct contain linear offset and scale for coordinate system
 */
struct offset{
    Vector2 coords; /**<  linear offset*/
    Vector2 scale;  /**<  scale (how many pix for 1 sing. seg.)*/
};

/**
 * @brief transform between 2 coordinate system (from Qadratic to Visual coords system)
 * @param[in] target        target of transform
 * @param[in] axis_offset   transform coefficents (offset and scale)
 * @return transformed Vector2
 */
Vector2 converQtoV(Vector2 target, offset axis_offset);

/**
 * @brief transform between 2 coordinate system (from Visal to Qadratic coords system)
 * @param[in] target        target of transform
 * @param[in] axis_offset   transform coefficents (offset and scale)
 * @return transformed Vector2
 */
Vector2 converVtoQ(Vector2 target, offset axis_offset);

/**
 * @brief Init window and set frame rate
 */
void visualInit();

/**
 * @brief Draw main axis based on offset 
 */
void drawMainAxis(offset axis_offset);

/**
 * @brief Draw axis and Grid based on offset 
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