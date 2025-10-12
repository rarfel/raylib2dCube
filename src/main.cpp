#include "raylib.h"
#include "../headers/logic.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");
    
    //Each Vector3 is a vertice/point in space
    Vector3 v1 = {100,100,-100};
    Vector3 v2 = {100,200,100};
    Vector3 v3 = {150,150,-100};
    
    Face face = {v1,v2,v3};

    int fov = 8000;

    bool withCircles = false;

    float angleAlpha = 0;
    float angleBeta = 0;
    float angleGamma = 0;

    // how much the angle change each iteration
    const float angleChange = 0.01;

    while (!WindowShouldClose())
    {
        // updtade angles
        if(IsKeyDown(KEY_ONE)) {angleAlpha += angleChange;}
        if(IsKeyDown(KEY_TWO)) {angleBeta += angleChange;}
        if(IsKeyDown(KEY_THREE)) {angleGamma += angleChange;}

        if(IsKeyDown(KEY_FOUR)) {angleAlpha -= angleChange;}
        if(IsKeyDown(KEY_FIVE)) {angleBeta -= angleChange;}
        if(IsKeyDown(KEY_SIX)) {angleGamma -= angleChange;}

        // enable small circles on the edges
        if(IsKeyPressed(KEY_SPACE)){withCircles = (withCircles) ? false : true;}

        // changes fov
        if(IsKeyDown(KEY_UP)){fov+= 100;}
        if(IsKeyDown(KEY_DOWN)){fov-= 100;}

        SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(BLACK);

        face = RotateXYZAxis({v1,v2,v3}, angleAlpha, angleBeta, angleGamma, fov);
        DrawFace(face, withCircles, PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}