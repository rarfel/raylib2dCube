#pragma once

#include <cmath>
#include <vector>

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
    Vector3 vec4 = {0,0,0};
};

struct FaceIndex
{
    int index[4] = {0,0,0,0};
};

// dx = cosy(sinzY + coszX) - sinyZ
float RotateXAxis(Vector3 vec, float angleBeta, float angleGamma)
{
    float sinBeta = std::sin(angleBeta);
    float sinGamma = std::sin(angleGamma);

    float cosBeta = std::cos(angleBeta);
    float cosGamma = std::cos(angleGamma);

    return cosBeta * (sinGamma * vec.y + cosGamma * vec.x) - sinBeta * vec.z;
}

// dy = sinx(cosyZ + siny(sinzY + coszX)) + cosx(coszY - sinzX)
float RotateYAxis(Vector3 vec, float angleAlpha, float angleBeta, float angleGamma)
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
float RotateZAxis(Vector3 vec, float angleAlpha, float angleBeta, float angleGamma)
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
Face ProjectedCoordinates(Face face, float fov)
{
    Face projectedFace;
    //subtracting the result from half the screen width/Height to centralize object

    projectedFace.vec1.x = HALF_WIDTH - ((face.vec1.x * fov) / (face.vec1.z + fov));
    projectedFace.vec2.x = HALF_WIDTH - ((face.vec2.x * fov) / (face.vec2.z + fov));
    projectedFace.vec3.x = HALF_WIDTH - ((face.vec3.x * fov) / (face.vec3.z + fov));
    projectedFace.vec4.x = HALF_WIDTH - ((face.vec4.x * fov) / (face.vec4.z + fov));

    projectedFace.vec1.y = HALF_HEIGHT - ((face.vec1.y * fov) / (face.vec1.z + fov));
    projectedFace.vec2.y = HALF_HEIGHT - ((face.vec2.y * fov) / (face.vec2.z + fov));
    projectedFace.vec3.y = HALF_HEIGHT - ((face.vec3.y * fov) / (face.vec3.z + fov));
    projectedFace.vec4.y = HALF_HEIGHT - ((face.vec4.y * fov) / (face.vec4.z + fov));

    projectedFace.vec1.z = face.vec1.z;
    projectedFace.vec2.z = face.vec2.z;
    projectedFace.vec3.z = face.vec3.z;
    projectedFace.vec4.z = face.vec4.z;

    return projectedFace;
}

// Rotates the points in all axis using the mathematical formula: https://en.wikipedia.org/wiki/3D_projection#Mathematical_formula
Face RotateXYZAxis(Face face, float angleAlpha, float angleBeta, float angleGamma, float fov)
{
    Face nFace;

    nFace.vec1.x = RotateXAxis(face.vec1,angleBeta,angleGamma);
    nFace.vec2.x = RotateXAxis(face.vec2,angleBeta,angleGamma);
    nFace.vec3.x = RotateXAxis(face.vec3,angleBeta,angleGamma);
    nFace.vec4.x = RotateXAxis(face.vec4,angleBeta,angleGamma);

    nFace.vec1.y = RotateYAxis(face.vec1,angleAlpha,angleBeta,angleGamma);
    nFace.vec2.y = RotateYAxis(face.vec2,angleAlpha,angleBeta,angleGamma);
    nFace.vec3.y = RotateYAxis(face.vec3,angleAlpha,angleBeta,angleGamma);
    nFace.vec4.y = RotateYAxis(face.vec4,angleAlpha,angleBeta,angleGamma);

    nFace.vec1.z = RotateZAxis(face.vec1,angleAlpha,angleBeta,angleGamma);
    nFace.vec2.z = RotateZAxis(face.vec2,angleAlpha,angleBeta,angleGamma);
    nFace.vec3.z = RotateZAxis(face.vec3,angleAlpha,angleBeta,angleGamma);
    nFace.vec4.z = RotateZAxis(face.vec4,angleAlpha,angleBeta,angleGamma);

    return ProjectedCoordinates(nFace, fov);
}

// Using the same function at Sebastian Lague Rasterizer git repo: https://github.com/SebLague/Software-Rasterizer/blob/main/Source/Core/Helpers/Maths.cs
bool TestIfInside(Vector3 &v1, Vector3 &v2, Vector3 &v3)
{
    return (v3.x - v1.x) * (v2.y - v1.y) + (v3.y - v1.y) * (v1.x - v2.x) >= 0;
}

bool TestIfFaceValid(Vector3 &v1, Vector3 &v2, Vector3 &v3, Vector3 point)
{
    bool edge1 = TestIfInside(v1, v2, point);
    bool edge2 = TestIfInside(v2, v3, point);
    bool edge3 = TestIfInside(v3, v1, point);
    return TestIfInside(v1, v2, point) and TestIfInside(v2, v3, point) and TestIfInside(v3, v1, point);
}

void DrawFaceTriangle(Vector3 &v1, Vector3 &v2, Vector3 &v3, Vector3 &v4)
{
    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            bool face1 = TestIfFaceValid(v1,v2,v3,{float(i),float(j),0});
            bool face2 = TestIfFaceValid(v1,v3,v4,{float(i),float(j),0});
            if(face1 or face2)
            DrawPixel(i, j, {(unsigned char)(int((i)/(3.85))%255), (unsigned char)(int((j)/(2.85))%255), 0, 255});
        }
    }
}

// function that draws the face of a 3d object
void DrawFace(Face face, bool withCircles, bool solidTriangles, Color color)
{
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
        DrawFaceTriangle(face.vec1, face.vec2, face.vec3, face.vec4);
    }else
    {
        DrawLine(face.vec1.x, face.vec1.y, face.vec2.x, face.vec2.y, color);
        DrawLine(face.vec2.x, face.vec2.y, face.vec3.x, face.vec3.y, color);
        DrawLine(face.vec3.x, face.vec3.y, face.vec1.x, face.vec1.y, color);

        if(face.vec4.x != 0 and face.vec4.y != 0 and face.vec4.z != 0)
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