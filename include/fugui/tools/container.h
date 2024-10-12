#pragma once
namespace fugui {
struct Vector2
{
	static Vector2 Zero;
	float x;
	float y;
};

bool operator==(const Vector2& x, const Vector2& y);

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};
}
