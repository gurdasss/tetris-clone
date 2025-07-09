#include <raylib.h>
#include <array> // for std::array

#ifndef TETRIMINO_H
#define TETRIMINO_H

class Tetrimino
{

	static constexpr float s_tileW{20.0f};
	static constexpr float s_tileH{20.0f};
	static constexpr float s_scale{3.0f};

public:
	enum Type
	{
		O,
		S,
		Z,
		L,
		J,
		T,
		// I,
	};

	static constexpr float s_tetriminoW{s_tileW * s_scale};
	static constexpr float s_tetriminoH{s_tileH * s_scale};

	Tetrimino(float x, float y, Type type);

	void moveDown();
	void moveLeft();
	void moveRight();

	void rotate90DegClockwise();

	void draw(bool debug = false) const;

private:
	Vector2 m_refPos{0.0f, 0.0f};
	std::array<Vector4, 4> m_tiles{};

	void arrangeTiles(Type type);
	void moveAcrossX(float direction);
};

#endif