#ifndef __VISUAL__
#define __VISUAL__

#include "raylib.h"
#include "quade.h"

#define WINDOWS_SIZE 1000
#define STANDART_SCALE 50

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
 * @param[in] axis_offset on this offset based axis visual
 */
void drawMainAxis(offset axis_offset);

/**
 * @brief Draw axis and Grid based on offset 
 * @param[in] axis_offset on this offset based grid
 */
void drawMainGrid(Vector2 axis_offset);

/**
 * @brief Draw quadratic equation based on offset
 * @param[in] q           quadratic equation for dawing
 * @param[in] axis_offset on this offset based position of quadratic equation on screan
 */
void drawQadraticEquation( QuadraticEquation *q, Vector2 offset);

/**
 * @brief  change offset and scale based on pressed key
 * H - return to vertex of parabola
 * O - return to (0, 0)
 * S - set standart scale (STANDART_SCALE)
 * @param[in] q                quadratic equation for vertex
 * @param[in, out] axis_offset offset to change
 */
void keyHandlder(QuadraticEquation *q, offset *vis_offset);

/**
 * @brief change offset and scale based on mouse moving
 * @param[in, out] axis_offset offset to change
 */
void mouseHandler(Vector2 *offset);

/**
 * @brief main visual loop, processing mouse input and draw qadratic equation and grid
 * @param[in] q quadratic equation for dawing
 */
void visualLoop(QuadraticEquation *q);

#endif