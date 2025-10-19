#include "raylib.h"
#include "../headers/logic.h"
#include "../headers/fileReader.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");
    
    std::vector<Vector3> verticesOBJ;
    std::vector<FaceIndex> facesOBJ;
    std::vector<FaceIndex>::iterator iteratorfacesOBJ;
    std::vector<Face> faces;

    float scaler = 100;

    //grabbing vertices values and the link between then
    ReadOBJFile("res/cube.obj", verticesOBJ, facesOBJ);
    //scaling values by a scaler because the raw values are [-1 < value < 1]
    ScaleVertice(verticesOBJ, scaler);

    float fov = 1000;

    bool withCircles = false;
    bool solidTriangles = false;

    float angleAlpha = 0;
    float angleBeta = 0;
    float angleGamma = 0;

    // how much the angle change each iteration
    const float angleChange = 0.01;

    //linking the vertices in the correspondent faces
    for(iteratorfacesOBJ = facesOBJ.begin(); iteratorfacesOBJ != facesOBJ.end(); iteratorfacesOBJ++)
    {
        if(iteratorfacesOBJ->index[3] != -1)
            faces.push_back({verticesOBJ.at(iteratorfacesOBJ->index[0]), verticesOBJ.at(iteratorfacesOBJ->index[1]), verticesOBJ.at(iteratorfacesOBJ->index[2]),verticesOBJ.at(iteratorfacesOBJ->index[3])});
        else
            faces.push_back({verticesOBJ.at(iteratorfacesOBJ->index[0]), verticesOBJ.at(iteratorfacesOBJ->index[1]), verticesOBJ.at(iteratorfacesOBJ->index[2])});
    }

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

        for(auto it = faces.begin(); it != faces.end(); it++)
        {
            DrawFace(RotateXYZAxis(*it, angleAlpha, angleBeta, angleGamma, fov, scaler), withCircles, solidTriangles, fov, scaler);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}