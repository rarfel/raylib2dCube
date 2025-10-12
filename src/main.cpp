#include "raylib.h"
#include "../headers/logic.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");
    
    //taking values mannually from cube.obj for now
    float scaler = 100;
    Vector3 v0 = {-(1 * scaler),-(1 * scaler),(1 * scaler)};
    Vector3 v1 = {(1 * scaler),-(1 * scaler),(1 * scaler)};
    Vector3 v2 = {-(1 * scaler),(1 * scaler),(1 * scaler)};
    Vector3 v3 = {(1 * scaler),(1 * scaler),(1 * scaler)};
    Vector3 v4 = {-(1 * scaler),(1 * scaler),-(1 * scaler)};
    Vector3 v5 = {(1 * scaler),(1 * scaler),-(1 * scaler)};
    Vector3 v6 = {(1 * scaler),-(1 * scaler),-(1 * scaler)};
    Vector3 v7 = {-(1 * scaler),-(1 * scaler),-(1 * scaler)};
    
    // linking vertices mannually from cube.obj for now
    Face face0 = {v0,v1,v2};
    Face face1 = {v1,v2,v3};
    Face face2 = {v4,v5,v6};
    Face face3 = {v4,v6,v7};
    Face face4 = {v1,v3,v5};
    Face face5 = {v1,v5,v6};
    Face face6 = {v2,v4,v7};
    Face face7 = {v0,v2,v7};
    Face face8 = {v0,v1,v7};
    Face face9 = {v1,v6,v7};
    Face face10 = {v2,v4,v5};
    Face face11 = {v2,v3,v5};

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

        if(IsKeyDown(KEY_ENTER)){angleAlpha += angleChange; angleBeta += angleChange; angleGamma += angleChange;}
        if(IsKeyDown(KEY_LEFT_SHIFT)){angleAlpha -= angleChange; angleBeta -= angleChange; angleGamma -= angleChange;}

        // enable small circles on the edges
        if(IsKeyPressed(KEY_SPACE)){withCircles = (withCircles) ? false : true;}

        // changes fov
        if(IsKeyPressed(KEY_UP)){fov+= 100;}
        if(IsKeyPressed(KEY_DOWN)){fov-= 100;}

        SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(BLACK);

        face0 = RotateXYZAxis({v0,v1,v2}, angleAlpha, angleBeta, angleGamma, fov);
        face1 = RotateXYZAxis({v1,v2,v3}, angleAlpha, angleBeta, angleGamma, fov);
        face2 = RotateXYZAxis({v4,v5,v6}, angleAlpha, angleBeta, angleGamma, fov);
        face3 = RotateXYZAxis({v4,v6,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face4 = RotateXYZAxis({v1,v3,v5}, angleAlpha, angleBeta, angleGamma, fov);
        face5 = RotateXYZAxis({v1,v5,v6}, angleAlpha, angleBeta, angleGamma, fov);
        face6 = RotateXYZAxis({v2,v4,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face7 = RotateXYZAxis({v0,v2,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face8 = RotateXYZAxis({v0,v1,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face9 = RotateXYZAxis({v1,v6,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face10 = RotateXYZAxis({v2,v4,v5}, angleAlpha, angleBeta, angleGamma, fov);
        face11 = RotateXYZAxis({v2,v3,v5}, angleAlpha, angleBeta, angleGamma, fov);

        DrawFace(face0, withCircles, PURPLE);
        DrawFace(face1, withCircles, PURPLE);
        DrawFace(face2, withCircles, PURPLE);
        DrawFace(face3, withCircles, PURPLE);
        DrawFace(face4, withCircles, PURPLE);
        DrawFace(face5, withCircles, PURPLE);
        DrawFace(face6, withCircles, PURPLE);
        DrawFace(face7, withCircles, PURPLE);
        DrawFace(face8, withCircles, PURPLE);
        DrawFace(face9, withCircles, PURPLE);
        DrawFace(face10, withCircles, PURPLE);
        DrawFace(face11, withCircles, PURPLE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}