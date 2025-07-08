#include "Tetrimino.h"
#include <raylib.h>
#include <raymath.h> // for Vector2Rotate
#include <cmath>	 // for std::abs

Tetrimino::Tetrimino(const Vector2 &position,
					 Type type,
					 const Color &color)
	: m_color{color}
{

	m_refRec.x = position.x - m_refRec.width / 2.0f;
	m_refRec.y = position.y - m_refRec.height / 2.0f;

	arrangeTiles(type);
}

void Tetrimino::arrangeTiles(Type type)
{
	switch (type)
	{
	case T:
		m_tiles[0] = {m_refRec.x, m_refRec.y, 1, 0};
		m_tiles[1] = {m_refRec.x + s_tileW, m_refRec.y, 1, 1};
		m_tiles[2] = {m_refRec.x + s_tileW * 2, m_refRec.y, 0, 1};
		m_tiles[3] = {m_refRec.x + s_tileW, m_refRec.y + s_tileH, 0, 0};
		break;

	default:
		break;
	}
}

void Tetrimino::draw(bool debug) const
{
	if (debug)
	{
		DrawRectangleRec(m_refRec, LIGHTGRAY);

		for (const Vector4 &tilePos : m_tiles)
			DrawCircle(static_cast<int>(tilePos.x),
					   static_cast<int>(tilePos.y),
					   2.5f, BLACK);
	}

	for (const Vector4 &tilePos : m_tiles)
		DrawRectangle(static_cast<int>(tilePos.x),
					  static_cast<int>(tilePos.y),
					  s_tileW,
					  s_tileH,
					  m_color);
}

void Tetrimino::rotate90DegClockwise()
{
	static float rotationDeg{};

	if (rotationDeg >= 360.0f)
		rotationDeg = 0;

	float tileRotationRad{rotationDeg * (PI / 180.0f)};

	for (Vector4 &tile : m_tiles)
	{
		Vector2 rotatedPoint{
			Vector2Rotate(Vector2{tile.z, tile.w}, tileRotationRad)};

		float steps{(3.0f - (std::abs(rotatedPoint.x) +
							 std::abs(rotatedPoint.y)))};

		tile.x += rotatedPoint.x * s_tileW * steps;
		tile.y += rotatedPoint.y * s_tileH * steps;
	}

	rotationDeg += 90.0f;
}