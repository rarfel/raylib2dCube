#include "raylib.h"

#define WIDTH 980
#define HEIGHT 720

int main(void)
{
    int i = 0;
    bool turning = false;
    InitWindow(WIDTH, HEIGHT, "Creating a line first");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(i,0,WIDTH,HEIGHT,WHITE);
            DrawLine(i,HEIGHT,WIDTH,0,WHITE);
            if(turning)
            {
                i--;
                if(i < 0)
                    turning = false;
            }
            else if(!turning)
            {
                i++;
                if(i >= WIDTH)
                    turning = true;
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}