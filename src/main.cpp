#include "raylib.h"
#include "../headers/logic.h"
#include "../headers/fileReader.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "3d Objects");
    
    std::vector<Vector3> verticesOBJ;
    std::vector<FaceIndex> facesOBJ;
    std::vector<FaceIndex>::iterator iteratorfacesOBJ;

    float scaler = 100;

    //grabbing vertices values and the link between then
    ReadOBJFile("res/cube.obj", verticesOBJ, facesOBJ);
    //scaling values by a scaler because the raw values are [-1 < value < 1]
    ScaleVertice(verticesOBJ, scaler);

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
        for(iteratorfacesOBJ = facesOBJ.begin(); iteratorfacesOBJ != facesOBJ.end(); iteratorfacesOBJ++)
        {
            Face face = {verticesOBJ.at(iteratorfacesOBJ->index[0]), verticesOBJ.at(iteratorfacesOBJ->index[1]), verticesOBJ.at(iteratorfacesOBJ->index[2])};
            Face nface = {face.vec1,face.vec2,face.vec3};
            face = RotateXYZAxis(nface, angleAlpha, angleBeta, angleGamma, fov);
            DrawFace(face, withCircles, solidTriangles, {(unsigned char)(int(face.vec3.x)%255), (unsigned char)(int(face.vec2.y)%255), (unsigned char)(int(face.vec1.z)%255), 255});
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}