#include "raylib.h"
#include "../headers/logic.h"

#define WIDTH 980
#define HEIGHT 720

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");

    float x1 = 200;
    float y1 = 200;
    float z1 = 1;

    float x2 = 400;
    float y2 = 400;
    float z2 = 1;

    float x3 = 400;
    float y3 = 200;
    float z3 = 1;
    
    Vector3 v1 = {x1,y1,z1};
    Vector3 v2 = {x2,y2,z2};
    Vector3 v3 = {x3,y3,z3};
    
    Vector3 nv1;
    Vector3 nv2;
    Vector3 nv3;

    int fov = 100;

    bool withCircles = false;

    float angleAlpha = 0;
    float angleBeta = 0;
    float angleGamma = 0;

    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_ONE)) {angleAlpha += 0.005;}
        if(IsKeyDown(KEY_TWO)) {angleBeta += 0.005;}
        if(IsKeyDown(KEY_THREE)) {angleGamma += 0.005;}

        if(IsKeyDown(KEY_FOUR)) {angleAlpha -= 0.005;}
        if(IsKeyDown(KEY_FIVE)) {angleBeta -= 0.005;}
        if(IsKeyDown(KEY_SIX)) {angleGamma -= 0.005;}

        if(IsKeyPressed(KEY_SPACE)){withCircles = (withCircles) ? false : true;}

        BeginDrawing();
        
        nv1 = RotateXYZAxis({x1,y1,z1},angleAlpha,angleBeta,angleGamma);
        nv2 = RotateXYZAxis({x2,y2,z2},angleAlpha,angleBeta,angleGamma);
        nv3 = RotateXYZAxis({x3,y3,z3},angleAlpha,angleBeta,angleGamma);

        v1 = ProjectedCoordinates(nv1,fov);
        v2 = ProjectedCoordinates(nv2,fov);
        v3 = ProjectedCoordinates(nv3,fov);

        ClearBackground(BLACK);
        DrawTriangleHollow(v1, v2, v3, withCircles, PURPLE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}