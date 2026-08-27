#include "visual.h"

#include <math.h>
#include "raylib.h"
#include "quade.h"

static double pix_per_I = 20, pix_per_J = 20;

void visualInit(){
    InitWindow( WINDOWS_SIZE, WINDOWS_SIZE, "Quadratic equation");
    SetTargetFPS(60);
    Image icon =  LoadImage("icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void drawMainGrid(Vector2 axis_offset){
    for (float d = 0; d - abs(axis_offset.y) <  WINDOWS_SIZE; d += pix_per_I){
        Vector2 p1 = { 0, d + axis_offset.y};
        Vector2 p2 = {float(WINDOWS_SIZE), d + axis_offset.y};
        DrawLineEx(p1, p2, 2, GRAY);
        Vector2 p3 = { 0, - d + axis_offset.y};
        Vector2 p4 = {float(WINDOWS_SIZE), - d + axis_offset.y};
        DrawLineEx(p3, p4, 2, GRAY);
    }
    for (float d = 0; d - abs(axis_offset.x) <  WINDOWS_SIZE; d += pix_per_J){
        Vector2 p1 = { d + axis_offset.x, 0};
        Vector2 p2 = { d + axis_offset.x, float(WINDOWS_SIZE)};
        DrawLineEx(p1, p2, 2, GRAY);
        Vector2 p3 = { - d + axis_offset.x, 0};
        Vector2 p4 = { - d + axis_offset.x, float(WINDOWS_SIZE)};
        DrawLineEx(p3, p4, 2, GRAY);
    }
    Vector2 p1 = { 0, axis_offset.y};
    Vector2 p2 = {float(WINDOWS_SIZE), axis_offset.y};
    DrawLineEx(p1, p2, 4, DARKGRAY);
    Vector2 p3 = { axis_offset.x, 0};
    Vector2 p4 = { axis_offset.x, float(WINDOWS_SIZE)};
    DrawLineEx(p3, p4, 4, DARKGRAY);
}

void drawQuadraticEquation( QuadraticEquation *q, Vector2 offset){
    for (int X = 0; X + 1 < WINDOWS_SIZE; X += 1){
        Vector2 p1 = {float(X), float(offset.y - calcValQuadraticEquation(q, (X - offset.x) / pix_per_I) * pix_per_J)};
        Vector2 p2 = {float(X + 1), float(offset.y - calcValQuadraticEquation(q, (X + 1 - offset.x) / pix_per_I) * pix_per_J)};
        DrawLineEx( p1, p2, 5, DARKGREEN);
    }
}

void mouseHandler(Vector2 *offset){
    static Vector2 mouse = {};
    if (IsMouseButtonPressed(0)){
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
    }
    if (IsMouseButtonDown(0)){
        offset->x -= (mouse.x - GetMouseX());
        offset->y -= (mouse.y - GetMouseY());
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
    }
    float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.0 && (pix_per_I + wheel_change > 1) && (pix_per_J + wheel_change > 1)){
        pix_per_I += wheel_change;
        pix_per_J += wheel_change;
    }
}

void visualLoop(QuadraticEquation *q){
    Vector2 offset = { float(WINDOWS_SIZE / 2.0 - (-q->b / (2 * q->a)) * pix_per_I), float(WINDOWS_SIZE / 2.0 + calcValQuadraticEquation(q, (-q->b / (2 * q->a))) * pix_per_J)};
    while (!IsWindowReady()){}
    while(!WindowShouldClose()){
        mouseHandler(&offset);        
        BeginDrawing();
        ClearBackground(WHITE);
        drawMainGrid(offset);
        drawQuadraticEquation(q, offset);
        EndDrawing();
    }
}