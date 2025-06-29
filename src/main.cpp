#include <raylib.h>

int main()
{

    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "Tetris");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}