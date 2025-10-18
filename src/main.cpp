#include "raylib.h"

#define WIDTH 980
#define HEIGHT 720

int main(void)
{
    const int squareSize = 1;
    InitWindow(WIDTH, HEIGHT, "Creating colored grid");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0; i < WIDTH; i++)
            for(int j = 0; j < HEIGHT; j++)
                //The rgba values are stored in unsigned char, so converting is a must
                DrawPixel(i, j, {(unsigned char)(int((i*squareSize)/(3.85))%255), (unsigned char)(int((j*squareSize)/(2.85))%255), 0, 255});
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}