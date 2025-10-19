#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <random>

#define WIDTH 980
#define HEIGHT 720

#define HALF_WIDTH WIDTH/2
#define HALF_HEIGHT HEIGHT/2

// A face is defined by 3 vertices
struct Face
{
    Vector3 vec1 = {0,0,0};
    Vector3 vec2 = {0,0,0};
    Vector3 vec3 = {0,0,0};
    Vector3 vec4 = {-1,-1,-1};
};

// array that holds the vertices links, eg [1,2,3,-1] is a triangle, wheres [1,2,3,4] is a square
struct FaceIndex
{
    int index[4] = {-1,-1,-1,-1};
};

// dx = cosy(sinzY + coszX) - sinyZ
float RotateXAxis(Vector3 &vec, float angleBeta, float angleGamma)
{
    float sinBeta = std::sin(angleBeta);
    float sinGamma = std::sin(angleGamma);

    float cosBeta = std::cos(angleBeta);
    float cosGamma = std::cos(angleGamma);

    return cosBeta * (sinGamma * vec.y + cosGamma * vec.x) - sinBeta * vec.z;
}

// dy = sinx(cosyZ + siny(sinzY + coszX)) + cosx(coszY - sinzX)
float RotateYAxis(Vector3 &vec, float angleAlpha, float angleBeta, float angleGamma)
{
    float sinAlpha = std::sin(angleAlpha);
    float sinBeta = std::sin(angleBeta);
    float sinGamma = std::sin(angleGamma);

    float cosAlpha = std::cos(angleAlpha);
    float cosBeta = std::cos(angleBeta);
    float cosGamma = std::cos(angleGamma);

    return sinAlpha * (cosBeta * vec.z + sinBeta * (sinGamma * vec.y + cosGamma * vec.x)) + cosAlpha * (cosGamma * vec.y - sinGamma * vec.x);
}

// dz = cosx(cosyZ + siny(sinzY + coszX)) - sinx(coszY - sinzX)
float RotateZAxis(Vector3 &vec, float angleAlpha, float angleBeta, float angleGamma)
{
    float sinAlpha = std::sin(angleAlpha);
    float sinBeta = std::sin(angleBeta);
    float sinGamma = std::sin(angleGamma);

    float cosAlpha = std::cos(angleAlpha);
    float cosBeta = std::cos(angleBeta);
    float cosGamma = std::cos(angleGamma);

    return cosAlpha * (cosBeta * vec.z + sinBeta * (sinGamma * vec.y + cosGamma * vec.x)) - sinAlpha * (cosGamma * vec.y - sinGamma * vec.x);
}

// projected = (x or y) * fov / z + fov
Face ProjectedCoordinates(Face &face, float fov, float scaler)
{
    Face projectedFace;
    //subtracting the result from half the screen width/Height to centralize object

    projectedFace.vec1.x = HALF_WIDTH - ((face.vec1.x * fov) /  (face.vec1.z + fov));
    projectedFace.vec2.x = HALF_WIDTH - ((face.vec2.x * fov) /  (face.vec2.z + fov));
    projectedFace.vec3.x = HALF_WIDTH - ((face.vec3.x * fov) /  (face.vec3.z + fov));
    projectedFace.vec4.x = HALF_WIDTH - ((face.vec4.x * fov) /  (face.vec4.z + fov));

    projectedFace.vec1.y = HALF_HEIGHT - ((face.vec1.y * fov) /  (face.vec1.z + fov));
    projectedFace.vec2.y = HALF_HEIGHT - ((face.vec2.y * fov) /  (face.vec2.z + fov));
    projectedFace.vec3.y = HALF_HEIGHT - ((face.vec3.y * fov) /  (face.vec3.z + fov));
    projectedFace.vec4.y = HALF_HEIGHT - ((face.vec4.y * fov) /  (face.vec4.z + fov));

    projectedFace.vec1.z = face.vec1.z;
    projectedFace.vec2.z = face.vec2.z;
    projectedFace.vec3.z = face.vec3.z;
    projectedFace.vec4.z = face.vec4.z;

    return projectedFace;
}

// Rotates the points in all axis using the mathematical formula: https://en.wikipedia.org/wiki/3D_projection#Mathematical_formula
Face RotateXYZAxis(Face face, float angleAlpha, float angleBeta, float angleGamma, float fov, float scaler)
{
    Face nFace;
    
    nFace.vec1.x = RotateXAxis(face.vec1,angleBeta,angleGamma);
    nFace.vec2.x = RotateXAxis(face.vec2,angleBeta,angleGamma);
    nFace.vec3.x = RotateXAxis(face.vec3,angleBeta,angleGamma);
    
    nFace.vec1.y = RotateYAxis(face.vec1,angleAlpha,angleBeta,angleGamma);
    nFace.vec2.y = RotateYAxis(face.vec2,angleAlpha,angleBeta,angleGamma);
    nFace.vec3.y = RotateYAxis(face.vec3,angleAlpha,angleBeta,angleGamma);
    
    nFace.vec1.z = RotateZAxis(face.vec1,angleAlpha,angleBeta,angleGamma);
    nFace.vec2.z = RotateZAxis(face.vec2,angleAlpha,angleBeta,angleGamma);
    nFace.vec3.z = RotateZAxis(face.vec3,angleAlpha,angleBeta,angleGamma);
    
    if(face.vec4.x != -1 and face.vec4.y != -1 and face.vec4.z != -1)
    {
        nFace.vec4.x = RotateXAxis(face.vec4,angleBeta,angleGamma);
        nFace.vec4.y = RotateYAxis(face.vec4,angleAlpha,angleBeta,angleGamma);
        nFace.vec4.z = RotateZAxis(face.vec4,angleAlpha,angleBeta,angleGamma);
    }

    return ProjectedCoordinates(nFace, fov, scaler);
}

// Using the same function at Sebastian Lague Rasterizer git repo: https://github.com/SebLague/Software-Rasterizer/blob/main/Source/Core/Helpers/Maths.cs
float TestIfInside(Vector3 &v1, Vector3 &v2, Vector3 &v3)
{
    return (v3.x - v1.x) * (v2.y - v1.y) + (v3.y - v1.y) * (v1.x - v2.x);
}

bool TestIfFaceValid(Vector3 &v1, Vector3 &v2, Vector3 &v3, Vector3 point)
{
    float edge1 = TestIfInside(v1, v2, point);
    float edge2 = TestIfInside(v2, v3, point);
    float edge3 = TestIfInside(v3, v1, point);
    bool inTriangle = (edge1 >= 0 and edge2 >= 0 and edge3 >= 0);

    float totalArea = (edge1 + edge2 + edge3);
    float invAreaSum = 1 / totalArea;

    return inTriangle && totalArea > 0;
}

void DrawFaceTriangle(Vector3 &v1, Vector3 &v2, Vector3 &v3, Color &color)
{
    const float minX = std::min(std::min(v1.x, v2.x), v3.x);
    const float maxX = std::max(std::max(v1.x, v2.x), v3.x);

    const float minY = std::min(std::min(v1.y, v2.y), v3.y);
    const float maxY = std::max(std::max(v1.y, v2.y), v3.y);

    for(float i = minX; i < maxX; i++)
    {
        for(float j = minY; j < maxY; j++)
        {
            bool face = TestIfFaceValid(v1,v2,v3,{i,j,0});
            if(face)
                DrawPixel(i, j, color);
        }
    }
}

Color VectorToColor(Vector3 &vec, float scaler)
{
    return {(unsigned char)((int)(vec.x*scaler)%255), (unsigned char)((int)(vec.y*scaler)%255), (unsigned char)((int)(vec.z*scaler)%255), 255};
}

// function that draws the face of a 3d object
void DrawFace(Face face, bool withCircles, bool solidTriangles, float fov, float scaler)
{
    float distX = 0;
    float distY = 0;
    float distZ = 0;

    distX += (face.vec1.x * fov) / (face.vec1.z + fov);
    distY += (face.vec1.y * fov) / (face.vec1.z + fov);
    distZ += face.vec1.z;

    distX += (face.vec2.x * fov) / (face.vec2.z + fov);
    distY += (face.vec2.y * fov) / (face.vec2.z + fov);
    distZ += face.vec2.z;

    distX += (face.vec3.x * fov) / (face.vec3.z + fov);
    distY += (face.vec3.y * fov) / (face.vec3.z + fov);
    distZ += face.vec3.z;

    distX += (face.vec4.x * fov) / (face.vec4.z + fov);
    distY += (face.vec4.y * fov) / (face.vec4.z + fov);
    distZ += face.vec4.z;

    Vector3 dist = {distX, distY, distZ};

        Color color = VectorToColor(dist, scaler);
        if(withCircles)
        {
            int circleSize = 5;
            DrawCircle(face.vec1.x, face.vec1.y, circleSize, color);
            DrawCircle(face.vec2.x, face.vec2.y, circleSize, color);
            DrawCircle(face.vec3.x, face.vec3.y, circleSize, color);
            DrawCircle(face.vec4.x, face.vec4.y, circleSize, color);
        }
        if(solidTriangles)
        {    
            DrawFaceTriangle(face.vec1, face.vec2, face.vec3, color);
            if((face.vec4.x != -1 and face.vec4.y != -1 and face.vec4.z != -1))
            DrawFaceTriangle(face.vec1, face.vec3, face.vec4, color);
        }
        else
        {
            DrawLine(face.vec1.x, face.vec1.y, face.vec2.x, face.vec2.y, color);
            DrawLine(face.vec2.x, face.vec2.y, face.vec3.x, face.vec3.y, color);
            DrawLine(face.vec3.x, face.vec3.y, face.vec1.x, face.vec1.y, color);
            
            if(face.vec4.x != -1 and face.vec4.y != -1 and face.vec4.z != -1)
            {   
                DrawLine(face.vec1.x, face.vec1.y, face.vec3.x, face.vec3.y, color);
                DrawLine(face.vec3.x, face.vec3.y, face.vec4.x, face.vec4.y, color);
                DrawLine(face.vec4.x, face.vec4.y, face.vec1.x, face.vec1.y, color);
            }
        }
}

//function that multiply the coordinates of a vertice by a scaler
void ScaleVertice(std::vector<Vector3> &verticesOBJ, float scaler)
{
    std::vector<Vector3>::iterator it;
    int aux = 0;

    for(it = verticesOBJ.begin(); it != verticesOBJ.end(); it++)
    {
        verticesOBJ.at(aux).x *= scaler;
        verticesOBJ.at(aux).y *= scaler;
        verticesOBJ.at(aux).z *= scaler;
        aux++;
    }
}