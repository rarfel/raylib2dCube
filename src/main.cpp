#include "raylib.h"

#define WIDTH 980
#define HEIGHT 720

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Creating a line first");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(0,0,WIDTH,HEIGHT,WHITE);
            DrawLine(0,HEIGHT,WIDTH,0,WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}