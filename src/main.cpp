#include "Tetrimino.h"
#include <raylib.h>

int main()
{

    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "Tetris");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

	Tetrimino t1{Vector2{screenW / 2.0f, screenH / 2.0f}, Tetrimino::T, RED};

	while (!WindowShouldClose())
	{

		// rotate the tile 90 degree around its pivot
		if (IsKeyPressed(KEY_UP))
		{

			t1.rotate90DegClockwise();
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);

		t1.draw(true);

		DrawFPS(0, 0);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}