#include "visual.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "quade.h"

#define constrain(x, low_b, high_b) ( (x > high_b) ? high_b : ((x < low_b) ? low_b : x) )

Vector2 converQtoV(Vector2 target, offset axis_offset){
    return (Vector2){
        target.x * axis_offset.scale.x + axis_offset.coords.x,
        target.y * axis_offset.scale.y + axis_offset.coords.y,};
}

Vector2 converVtoQ(Vector2 target, offset axis_offset){
    return (Vector2){
        (target.x - axis_offset.coords.x) / axis_offset.scale.x,
        (target.y - axis_offset.coords.y) / axis_offset.scale.y,};
}

void visualInit(){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow( WINDOWS_SIZE, WINDOWS_SIZE, "Quadratic equation");
    SetTargetFPS(60);
    Image icon =  LoadImage("icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void drawMainAxis(offset axis_offset){
    //Draw OX and OY
    Vector2 p1 = { 0, axis_offset.coords.y};
    Vector2 p2 = {float(WINDOWS_SIZE), axis_offset.coords.y};
    DrawLineEx(p1, p2, 4, DARKGRAY);
    DrawText("X", WINDOWS_SIZE - 25, axis_offset.coords.y - 35, 30, DARKGRAY);
    DrawTriangle((Vector2){WINDOWS_SIZE + 4, axis_offset.coords.y}, 
                 (Vector2){WINDOWS_SIZE - 30, axis_offset.coords.y - 10},
                 (Vector2){WINDOWS_SIZE - 30, axis_offset.coords.y + 10},
                 DARKGRAY);

    Vector2 p3 = { axis_offset.coords.x, 0};
    Vector2 p4 = { axis_offset.coords.x, float(WINDOWS_SIZE)};
    DrawLineEx(p3, p4, 4, DARKGRAY);
    DrawText("Y",  axis_offset.coords.x + 20, 10, 30, DARKGRAY);
    DrawTriangle((Vector2){axis_offset.coords.x, - 4}, 
                 (Vector2){axis_offset.coords.x - 10, 30},
                 (Vector2){axis_offset.coords.x + 10, 30},
                 DARKGRAY);
}

void drawMainGrid(offset axis_offset){
    char title[12] = "";
    
    int num_step = 1;
    if (axis_offset.scale.y < 20){
        num_step = int(40 / axis_offset.scale.y);
    }
    if (axis_offset.scale.y < 4){
        num_step = 10;
    }
    for (int line_cnt = int(-axis_offset.coords.y / axis_offset.scale.y), n = 1 + int((- axis_offset.coords.y + WINDOWS_SIZE)/ axis_offset.scale.y); line_cnt < n; line_cnt += num_step){
        // draw and subscribe lines parallel OX with positive Y
        Vector2 J = converQtoV((Vector2){0, float(line_cnt)}, axis_offset);
        Vector2 p1 = {0, J.y};
        Vector2 p2 = {float(WINDOWS_SIZE), J.y};
        DrawLineEx(p1, p2, 2, GRAY);
        sprintf(title, "%i", - line_cnt);
        DrawText(title, constrain(J.x + 3, 1 , WINDOWS_SIZE - 30), J.y + 5, 30, LIGHTGRAY);
    }
    num_step = 1;
    if (axis_offset.scale.x < 20){
        num_step = int(40 / axis_offset.scale.x);
    }
    if (axis_offset.scale.x < 4){
        num_step = 10;
    }    
    for (int line_cnt = int( - axis_offset.coords.x / axis_offset.scale.x), n = 1 + int((-axis_offset.coords.x + WINDOWS_SIZE)/ axis_offset.scale.x); line_cnt < n; line_cnt += num_step){
        // draw and subscribe lines parallel OY with positive X
        Vector2 I = converQtoV((Vector2){float(line_cnt), 0}, axis_offset);
        Vector2 p1 = { I.x, 0};
        Vector2 p2 = { I.x, float(WINDOWS_SIZE)};
        DrawLineEx(p1, p2, 2, GRAY);
        sprintf(title, "%i", line_cnt);
        DrawText(title, I.x + 3, constrain(I.y + 5, 3 , WINDOWS_SIZE - 30), 30, LIGHTGRAY);
    }
    drawMainAxis(axis_offset);
}

void drawQuadraticEquation( QuadraticEquation *q, offset vis_offset){
    for (int X = 0; X + 1 < WINDOWS_SIZE; X += 1){
        Vector2 p1 = {float(X), float(vis_offset.coords.y - calcValQuadraticEquation(q, (X - vis_offset.coords.x) / vis_offset.scale.x) * vis_offset.scale.y)};
        Vector2 p2 = {float(X + 1), float(vis_offset.coords.y - calcValQuadraticEquation(q, (X + 1 - vis_offset.coords.x) / vis_offset.scale.x) * vis_offset.scale.y)};
        DrawLineEx( p1, p2, 5, DARKGREEN);
    }
    //Drawing and subscribe roots
    char title[20] = "";
    Vector2 root1 = {};
    Vector2 root2 = {};
    switch (q->roots_count)
    {
    case ROOTS_TWO:
        root2 = converQtoV((Vector2){float(q->root2), 0}, vis_offset);
        DrawCircle(root2.x, root2.y, 6, RED);
        sprintf(title, "(%g, 0)", q->root2);
        DrawText(title, root2.x - 30, root2.y - 30, 30, RED);
    case ROOTS_ONE:
        root1 = converQtoV((Vector2){float(q->root1), 0}, vis_offset);
        DrawCircle(root1.x, root1.y, 6, RED);
        sprintf(title, "(%g, 0)", q->root1);
        DrawText(title, q->root1 * vis_offset.scale.x + vis_offset.coords.x - 30, vis_offset.coords.y - 30, 30, RED);
        break;
    default:
        break;
    }
}

void keyHandlder(QuadraticEquation *q, offset *vis_offset){
    if (IsKeyPressed(72)){
        if (q->a != 0){
            vis_offset->coords.x = WINDOWS_SIZE / 2.0 - (-q->b / (2 * q->a)) * vis_offset->scale.x;
            vis_offset->coords.y = WINDOWS_SIZE / 2.0 + calcValQuadraticEquation(q, (-q->b / (2 * q->a))) * vis_offset->scale.y;
        }
    }
    else if (IsKeyPressed(79)){
        vis_offset->coords.x = WINDOWS_SIZE / 2.0;
        vis_offset->coords.y = WINDOWS_SIZE / 2.0;
    }else if (IsKeyPressed(83)){
        vis_offset->scale.x = STANDART_SCALE;
        vis_offset->scale.y = STANDART_SCALE;
    }
}

void mouseHandler(offset *vis_offset){
    //Handle LKM for offset gaphics
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
    
    //Handle mouse wheel for scale gaphics
    float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.0 && (vis_offset->scale.x + wheel_change > 4) && (vis_offset->scale.y + wheel_change > 4)){
        if (!IsKeyDown(89)){
            vis_offset->coords.x = (vis_offset->coords.x - GetMouseX()) / vis_offset->scale.x;
            vis_offset->scale.x *= 1 + int(wheel_change * 50) / 1000.0;
            vis_offset->coords.x = vis_offset->coords.x * vis_offset->scale.x + GetMouseX();
        }
        if (!IsKeyDown(88)){
            vis_offset->coords.y = (vis_offset->coords.y - GetMouseY()) / vis_offset->scale.y;
            vis_offset->scale.y *= 1 + int(wheel_change * 50) / 1000.0;
            vis_offset->coords.y = vis_offset->coords.y * vis_offset->scale.y + GetMouseY();
        }
    }
}

void visualLoop(QuadraticEquation *q){
    checkLink(q);
    offset visual_offset = { {float(WINDOWS_SIZE / 2.0), float(WINDOWS_SIZE / 2.0)}, {STANDART_SCALE, STANDART_SCALE}};
    if (q->a != 0){
        visual_offset.coords.x -= (-q->b / (2 * q->a)) * visual_offset.scale.x;
        visual_offset.coords.y += calcValQuadraticEquation(q, (-q->b / (2 * q->a))) * visual_offset.scale.y;
        visual_offset.scale = { float(STANDART_SCALE * q->a), float(STANDART_SCALE * q->a)};
    }
    while (!IsWindowReady()){}
    while (!WindowShouldClose()){
        keyHandlder(q, &visual_offset);
        mouseHandler(&visual_offset);        
        BeginDrawing();
        ClearBackground(WHITE);
        drawMainGrid(visual_offset);
        drawQuadraticEquation(q, visual_offset);
        EndDrawing();
    }
}