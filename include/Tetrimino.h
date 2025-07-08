#include <raylib.h>
#include <array> // for std::array

#ifndef TETRIMINO_H
#define TETRIMINO_H

class Tetrimino
{
public:
	static constexpr float s_tileW{20.0f};
	static constexpr float s_tileH{20.0f};

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

	Tetrimino(const Vector2 &position, Type type, const Color &color);

	void rotate90DegClockwise();

	void draw(bool debug = false) const;

private:
	Rectangle m_refRec{0.0f, 0.0f, s_tileW * 3.0f, s_tileH * 3.0f};
	std::array<Vector4, 4> m_tiles{};
	Color m_color{};

	void arrangeTiles(Type type);
};

#endif