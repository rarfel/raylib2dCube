#include "raylib.h"
#include "../headers/logic.h"

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Creating colored grid");
    Vector3 vec1 = {HALF_WIDTH - 100, HALF_HEIGHT - 100, 100};
    Vector3 vec2 = {HALF_WIDTH + 100, HALF_HEIGHT - 100, 100};
    Vector3 vec3 = {HALF_WIDTH - 150, HALF_HEIGHT - 200, 100};
    Vector3 vec4 = {HALF_WIDTH - 150, HALF_HEIGHT + 200, 100};

    Vector3 vec5 = {HALF_WIDTH - 200, HALF_HEIGHT - 300, 100};
    Vector3 vec6 = {HALF_WIDTH + 300, HALF_HEIGHT - 100, 100};
    Vector3 vec7 = {HALF_WIDTH - 250, HALF_HEIGHT - 500, 100};
    Vector3 vec8 = {HALF_WIDTH - 150, HALF_HEIGHT + 200, 100};

    while (!WindowShouldClose())
    {
        SetTargetFPS(60);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawFace(vec1, vec2, vec3, vec4);
        DrawFace(vec5, vec6, vec7, vec8);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}