#include "Tetrimino.h"
#include <raylib.h>

int main()
{

    constexpr int screenW{800};
    constexpr int screenH{450};

    InitWindow(screenW, screenH, "Tetris");

    constexpr int targetFPS{60};
    SetTargetFPS(targetFPS);

	Tetrimino t1{
		screenW / 2.0f - (Tetrimino::s_tetriminoW / 2.0f),
		100 - (Tetrimino::s_tetriminoH / 2.0f),
		Tetrimino::J,
	};

	while (!WindowShouldClose())
	{
#if 0
		static int s_frameCounter{};
		constexpr int tileFPS{2};

		// update the tile's Y position
		// after (targetFPS / tileFPS) frame(s)
		if (++s_frameCounter >= (targetFPS / tileFPS))
		{
			// update the Y position of both the tile
			// and optionally of refRec
			t1.moveDown();

			s_frameCounter = 0;
		}

		// increase the frame counter's count
		// so that tile's Y position will
		// update much more quickly
		if (IsKeyDown(KEY_DOWN))
			s_frameCounter += 10;

#endif
		// rotate the tile 90 degree around its pivot
		if (IsKeyPressed(KEY_UP))
			t1.rotate90DegClockwise();

		if (IsKeyPressed(KEY_LEFT))
			t1.moveLeft();
		else if (IsKeyPressed(KEY_RIGHT))
			t1.moveRight();

		BeginDrawing();

		ClearBackground(RAYWHITE);

		t1.draw(true);

		DrawFPS(0, 0);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}