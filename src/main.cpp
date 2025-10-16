#include "raylib.h"
#include "../headers/logic.h"
#include "../headers/fileReader.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");
    
    std::vector<Vector3> verticesOBJ;

    //taking values mannually from cube.obj for now
    float scaler = 100;
    verticesOBJ = ReadOBJFile("res/cube.obj");
    Vector3 v0 = {(verticesOBJ.at(0).x * scaler),(verticesOBJ.at(0).y * scaler),(verticesOBJ.at(0).z * scaler)};
    Vector3 v1 = {(verticesOBJ.at(1).x * scaler),(verticesOBJ.at(1).y * scaler),(verticesOBJ.at(1).z * scaler)};
    Vector3 v2 = {(verticesOBJ.at(2).x * scaler),(verticesOBJ.at(2).y * scaler),(verticesOBJ.at(2).z * scaler)};
    Vector3 v3 = {(verticesOBJ.at(3).x * scaler),(verticesOBJ.at(3).y * scaler),(verticesOBJ.at(3).z * scaler)};
    Vector3 v4 = {(verticesOBJ.at(4).x * scaler),(verticesOBJ.at(4).y * scaler),(verticesOBJ.at(4).z * scaler)};
    Vector3 v5 = {(verticesOBJ.at(5).x * scaler),(verticesOBJ.at(5).y * scaler),(verticesOBJ.at(5).z * scaler)};
    Vector3 v6 = {(verticesOBJ.at(6).x * scaler),(verticesOBJ.at(6).y * scaler),(verticesOBJ.at(6).z * scaler)};
    Vector3 v7 = {(verticesOBJ.at(7).x * scaler),(verticesOBJ.at(7).y * scaler),(verticesOBJ.at(7).z * scaler)};
    
    // linking vertices mannually from cube.obj for now
    Face face0 = {v1,v2,v3};
    Face face1 = {v7,v6,v5};
    Face face2 = {v4,v5,v1};
    Face face3 = {v5,v6,v2};
    Face face4 = {v2,v6,v7};
    Face face5 = {v0,v3,v7};
    Face face6 = {v0,v1,v3};
    Face face7 = {v4,v7,v5};
    Face face8 = {v0,v4,v1};
    Face face9 = {v1,v5,v2};
    Face face10 = {v3,v2,v7};
    Face face11 = {v4,v0,v7};

    int fov = 1000;

    bool withCircles = false;
    bool solidTriangles = false;

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
        if(IsKeyPressed(KEY_H)){solidTriangles = (solidTriangles) ? false : true;}

        // changes fov
        if(IsKeyDown(KEY_UP)){fov+= 10;}
        if(IsKeyDown(KEY_DOWN)){fov-= 10;}

        SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(BLACK);

        face0 = RotateXYZAxis({v1,v2,v3}, angleAlpha, angleBeta, angleGamma, fov);
        face1 = RotateXYZAxis({v7,v6,v5}, angleAlpha, angleBeta, angleGamma, fov);
        face2 = RotateXYZAxis({v4,v5,v1}, angleAlpha, angleBeta, angleGamma, fov);
        face3 = RotateXYZAxis({v5,v6,v2}, angleAlpha, angleBeta, angleGamma, fov);
        face4 = RotateXYZAxis({v2,v6,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face5 = RotateXYZAxis({v0,v3,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face6 = RotateXYZAxis({v0,v1,v3}, angleAlpha, angleBeta, angleGamma, fov);
        face7 = RotateXYZAxis({v4,v7,v5}, angleAlpha, angleBeta, angleGamma, fov);
        face8 = RotateXYZAxis({v0,v4,v1}, angleAlpha, angleBeta, angleGamma, fov);
        face9 = RotateXYZAxis({v1,v5,v2}, angleAlpha, angleBeta, angleGamma, fov);
        face10 = RotateXYZAxis({v3,v2,v7}, angleAlpha, angleBeta, angleGamma, fov);
        face11 = RotateXYZAxis({v4,v0,v7}, angleAlpha, angleBeta, angleGamma, fov);

        DrawFace(face0, withCircles, solidTriangles, {170, 170, 0, 255});
        DrawFace(face1, withCircles, solidTriangles, {170, 170, 170, 255});
        DrawFace(face2, withCircles, solidTriangles, {0, 0, 170, 255});
        DrawFace(face3, withCircles, solidTriangles, {170, 85, 0, 255});
        DrawFace(face4, withCircles, solidTriangles, {0, 170, 0, 255});
        DrawFace(face5, withCircles, solidTriangles, {170, 0, 0, 255});
        DrawFace(face6, withCircles, solidTriangles, {170, 170, 0, 255});
        DrawFace(face7, withCircles, solidTriangles, {170, 170, 170, 255});
        DrawFace(face8, withCircles, solidTriangles, {0, 0, 170, 255});
        DrawFace(face9, withCircles, solidTriangles, {170, 85, 0, 255});
        DrawFace(face10, withCircles, solidTriangles, {0, 170, 0, 255});
        DrawFace(face11, withCircles, solidTriangles, {170, 0, 0, 255});

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
