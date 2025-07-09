#include "Tetrimino.h"
#include <raylib.h>
#include <raymath.h> // for Vector2Rotate
#include <cmath>	 // for std::abs

Tetrimino::Tetrimino(float x, float y, Type type)
	: m_refPos{Vector2{x, y}}
{
	arrangeTiles(type);
}

void Tetrimino::arrangeTiles(Type type)
{
	switch (type)
	{
	case O:
		m_tiles[0] = {
			m_refPos.x + (s_tileW / 2.0f),
			m_refPos.y + (s_tileH / 2.0f),
			0,
			0,
		};
		m_tiles[1] = {
			m_tiles[0].x + s_tileW,
			m_tiles[0].y,
			0,
			0,
		};
		m_tiles[2] = {
			m_tiles[0].x,
			m_tiles[0].y + s_tileH,
			0,
			0,
		};
		m_tiles[3] = {
			m_tiles[1].x,
			m_tiles[2].y,
			0,
			0,
		};
		break;

	case T:
		m_tiles[0] = {m_refPos.x, m_refPos.y, 1, 0};

		m_tiles[1] = {
			m_refPos.x + s_tileW,
			m_refPos.y,
			1,
			1,
		};

		m_tiles[2] = {
			m_tiles[1].x + s_tileW,
			m_refPos.y,
			0,
			1,
		};
		m_tiles[3] = {
			m_tiles[1].x,
			m_refPos.y + s_tileH,
			0,
			0,
		};
		break;

	case S:
		m_tiles[3] = {
			m_refPos.x + s_tileW * 2.0f,
			m_refPos.y + s_tileH,
			-1,
			1,
		};

		m_tiles[2] = {
			m_tiles[3].x - s_tileW,
			m_tiles[3].y,
			0,
			0,
		};

		m_tiles[1] = {
			m_tiles[2].x,
			m_tiles[3].y + s_tileH,
			-1,
			-1,
		};

		m_tiles[0] = {
			m_tiles[2].x - s_tileW,
			m_tiles[1].y,
			0,
			-1,
		};
		break;

	case Z:
		m_tiles[0] = {
			m_refPos.x,
			m_refPos.y + s_tileH,
			1,
			-1,
		};

		m_tiles[1] = {
			m_refPos.x + s_tileW,
			m_tiles[0].y,
			0,
			0,
		};

		m_tiles[2] = {
			m_tiles[1].x,
			m_tiles[0].y + s_tileH,
			-1,
			-1,
		};

		m_tiles[3] = {
			m_tiles[1].x + s_tileW,
			m_tiles[2].y,
			-1,
			0,
		};
		break;

	case L:
		m_tiles[0] = {
			m_refPos.x,
			m_refPos.y,
			1,
			0,
		};

		m_tiles[1] = {
			m_refPos.x,
			m_refPos.y + s_tileH,
			1,
			-1,
		};

		m_tiles[2] = {
			m_refPos.x,
			m_tiles[1].y + s_tileH,
			0,
			-1,
		};

		m_tiles[3] = {
			m_refPos.x + s_tileW,
			m_tiles[2].y,
			-1,
			-1,
		};

		break;

	case J:

		m_tiles[0] = {
			m_refPos.x + s_tileW * 2.0f,
			m_refPos.y,
			0,
			1,
		};

		m_tiles[1] = {
			m_tiles[0].x,
			m_refPos.y + s_tileH,
			-1,
			1,
		};

		m_tiles[2] = {
			m_tiles[0].x,
			m_tiles[1].y + s_tileH,
			-1,
			0,
		};

		m_tiles[3] = {
			m_tiles[0].x - s_tileW,
			m_tiles[2].y,
			-1,
			-1,
		};

		break;

	default:
		break;
	}
}

void Tetrimino::draw(bool debug) const
{
	if (debug)
	{
		DrawRectangle(static_cast<int>(m_refPos.x),
					  static_cast<int>(m_refPos.y),
					  s_tetriminoW,
					  s_tetriminoH,
					  LIGHTGRAY);

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
					  RED);
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

		float steps{(s_scale - (std::abs(rotatedPoint.x) +
								std::abs(rotatedPoint.y)))};

		tile.x += rotatedPoint.x * s_tileW * steps;
		tile.y += rotatedPoint.y * s_tileH * steps;
	}

	rotationDeg += 90.0f;
}

void Tetrimino::moveDown()
{
	m_refPos.y += s_tileH;

	for (Vector4 &tile : m_tiles)
		tile.y += s_tileH;
}

void Tetrimino::moveLeft()
{
	moveAcrossX(-1.0f);
}

void Tetrimino::moveRight()
{
	moveAcrossX(1.0f);
}

void Tetrimino::moveAcrossX(float direction)
{
	m_refPos.x += s_tileW * direction;

	for (Vector4 &tile : m_tiles)
		tile.x += s_tileW * direction;
}