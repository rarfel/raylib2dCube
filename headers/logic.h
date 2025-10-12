#include <iostream>
#include <cmath>

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

// Rotates the points in all axis
Vector3 RotateXYZAxis(Vector3 vec, float angleAlpha, float angleBeta, float angleGamma)
{
    Vector3 nVec;

    nVec.x = RotateXAxis(vec,angleBeta,angleGamma);
    nVec.y = RotateYAxis(vec,angleAlpha,angleBeta,angleGamma);
    nVec.z = RotateZAxis(vec,angleAlpha,angleBeta,angleGamma);

    return nVec;
}

// projected = (x or y) * fov / z + fov
Vector3 ProjectedCoordinates(Vector3 vec, float fov)
{
    Vector3 projected;

    projected.x = (vec.x * fov) / (vec.z + fov);
    projected.y = (vec.y * fov) / (vec.z + fov);
    projected.z = vec.z;

    return projected;
}

// function that draws a tringle with tiny circles on the edges
void DrawTriangleHollow(Vector3 v1, Vector3 v2, Vector3 v3, bool withCircles, Color color)
{
    if(withCircles)
    {
        int circleSize = 5;
        DrawCircle(v1.x, v1.y, circleSize, color);
        DrawCircle(v2.x, v2.y, circleSize, color);
        DrawCircle(v3.x, v3.y, circleSize, color);
    }
    DrawLine(v1.x, v1.y, v2.x, v2.y, color);
    DrawLine(v2.x, v2.y, v3.x, v3.y, color);
    DrawLine(v3.x, v3.y, v1.x, v1.y, color);
}