#include "raylib.h"

#define WIDTH 980
#define HEIGHT 720

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Creating a triangle");

    Vector2 v1 = {100,100};
    Vector2 v2 = {100,200};
    Vector2 v3 = {150,150};

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            //the DrawTriangle function creates a solid triangle
            // DrawTriangle(v1, v2, v3, WHITE);

            //If i want only the outline a have to use DrawLine 3 times
            DrawLine(v1.x, v1.y, v2.x, v2.y, WHITE);
            DrawLine(v2.x, v2.y, v3.x, v3.y, WHITE);
            DrawLine(v3.x, v3.y, v1.x, v1.y, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}