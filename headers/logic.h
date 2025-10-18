#pragma once

#define WIDTH 980
#define HEIGHT 720

#define HALF_WIDTH WIDTH/2
#define HALF_HEIGHT HEIGHT/2

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

void DrawFace(Vector3 &v1, Vector3 &v2, Vector3 &v3, Vector3 &v4)
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