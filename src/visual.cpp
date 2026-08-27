#include "visual.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "quade.h"

struct offset{
    Vector2 coords;
    Vector2 scale;
};

Vector2 converQtoV(Vector2 target, offset axis_offset){
    return (Vector2){
        target.x * axis_offset.scale.x + axis_offset.coords.x,
        target.y * axis_offset.scale.y + axis_offset.coords.y,};
}

void visualInit(){
    InitWindow( WINDOWS_SIZE, WINDOWS_SIZE, "Quadratic equation");
    SetTargetFPS(60);
    Image icon =  LoadImage("icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void drawMainGrid(offset axis_offset){
    char title[12] = "";
    int line_cnt = 0;
    int num_step = 1;
    if (axis_offset.scale.y < 20){
        num_step = int(40 / axis_offset.scale.y);
    }
    for (float d = 0, pix_step = axis_offset.scale.y * num_step; d - abs(axis_offset.coords.x) <  WINDOWS_SIZE; d += pix_step, line_cnt += num_step){
        Vector2 p1 = { 0, d + axis_offset.coords.y};
        Vector2 p2 = {float(WINDOWS_SIZE), d + axis_offset.coords.y};
        DrawLineEx(p1, p2, 2, GRAY);
        Vector2 p3 = { 0, - d + axis_offset.coords.y};
        Vector2 p4 = {float(WINDOWS_SIZE), - d + axis_offset.coords.y};
        DrawLineEx(p3, p4, 2, GRAY);
        sprintf(title, "%i", - line_cnt);
        DrawText(title, axis_offset.coords.x + 3, d + axis_offset.coords.y + 5, 30, LIGHTGRAY);
        sprintf(title, "%i", line_cnt);
        DrawText(title, axis_offset.coords.x + 3, - d + axis_offset.coords.y + 5, 30, LIGHTGRAY);
    }
    line_cnt = 0;
    num_step = 1;
    if (axis_offset.scale.x < 20){
        num_step = int(40 / axis_offset.scale.x);
    }    
    for (float d = 0, pix_step = axis_offset.scale.x * num_step; d - abs(axis_offset.coords.x) <  WINDOWS_SIZE; d += pix_step, line_cnt += num_step){
        Vector2 p1 = { d + axis_offset.coords.x, 0};
        Vector2 p2 = { d + axis_offset.coords.x, float(WINDOWS_SIZE)};
        DrawLineEx(p1, p2, 2, GRAY);
        Vector2 p3 = { - d + axis_offset.coords.x, 0};
        Vector2 p4 = { - d + axis_offset.coords.x, float(WINDOWS_SIZE)};
        DrawLineEx(p3, p4, 2, GRAY);
        sprintf(title, "%i", line_cnt);
        DrawText(title, d + axis_offset.coords.x + 3, axis_offset.coords.y + 5, 30, LIGHTGRAY);
        sprintf(title, "%i", - line_cnt);
        DrawText(title, -d + axis_offset.coords.x + 3, axis_offset.coords.y + 5, 30, LIGHTGRAY);
    }
    Vector2 p1 = { 0, axis_offset.coords.y};
    Vector2 p2 = {float(WINDOWS_SIZE), axis_offset.coords.y};
    DrawLineEx(p1, p2, 4, DARKGRAY);
    Vector2 p3 = { axis_offset.coords.x, 0};
    Vector2 p4 = { axis_offset.coords.x, float(WINDOWS_SIZE)};
    DrawLineEx(p3, p4, 4, DARKGRAY);
}

void drawQuadraticEquation( QuadraticEquation *q, offset vis_offset){
    for (int X = 0; X + 1 < WINDOWS_SIZE; X += 1){
        Vector2 p1 = {float(X), float(vis_offset.coords.y - calcValQuadraticEquation(q, (X - vis_offset.coords.x) / vis_offset.scale.x) * vis_offset.scale.y)};
        Vector2 p2 = {float(X + 1), float(vis_offset.coords.y - calcValQuadraticEquation(q, (X + 1 - vis_offset.coords.x) / vis_offset.scale.x) * vis_offset.scale.y)};
        DrawLineEx( p1, p2, 5, DARKGREEN);
    }
    char title[20] = "";
    Vector2 root1 = {};
    Vector2 root2 = {};
    switch (q->roots_count)
    {
    case ROOTS_ONE:
        root1 = converQtoV((Vector2){float(q->root1), 0}, vis_offset);
        DrawCircle(root1.x, root1.y, 6, RED);
        sprintf(title, "(%g, 0)", q->root1);
        DrawText(title, q->root1 * vis_offset.scale.x + vis_offset.coords.x - 30, vis_offset.coords.y - 30, 30, RED);
        break;

    case ROOTS_TWO:
        root1 = converQtoV((Vector2){float(q->root1), 0}, vis_offset);
        root2 = converQtoV((Vector2){float(q->root2), 0}, vis_offset);
        DrawCircle(root1.x, root1.y, 6, RED);
        DrawCircle(root2.x, root2.y, 6, RED);
        sprintf(title, "(%g, 0)", q->root1);
        DrawText(title, root1.x - 30, root1.y - 30, 30, RED);
        sprintf(title, "(%g, 0)", q->root2);
        DrawText(title, root2.x - 30, root2.y - 30, 30, RED);
        break;

    default:
        break;
    }
}

void mouseHandler(offset *vis_offset){
    static Vector2 mouse = {};
    if (IsMouseButtonPressed(0)){
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
    }
    if (IsMouseButtonDown(0)){
        vis_offset->coords.x -= (mouse.x - GetMouseX());
        vis_offset->coords.y -= (mouse.y - GetMouseY());
        mouse.x = GetMouseX();
        mouse.y = GetMouseY();
    }
    float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.0 && (vis_offset->scale.x + wheel_change > 4) && (vis_offset->scale.y + wheel_change > 4)){
        vis_offset->scale.x += wheel_change;
        vis_offset->scale.y += wheel_change;
    }
}

void visualLoop(QuadraticEquation *q){
    checkLink(q);
    offset visual_offset = { {float(WINDOWS_SIZE / 2.0), float(WINDOWS_SIZE / 2.0)}, {20, 20}};

    if (q->a != 0){
        visual_offset.coords.x -= (-q->b / (2 * q->a)) * visual_offset.scale.x;
        visual_offset.coords.y += calcValQuadraticEquation(q, (-q->b / (2 * q->a))) * visual_offset.scale.y;
    }
    while (!IsWindowReady()){}
    while (!WindowShouldClose()){
        mouseHandler(&visual_offset);        
        BeginDrawing();
        ClearBackground(WHITE);
        drawMainGrid(visual_offset);
        drawQuadraticEquation(q, visual_offset);
        EndDrawing();
    }
}