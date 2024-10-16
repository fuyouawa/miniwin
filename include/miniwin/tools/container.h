#pragma once
namespace miniwin {
struct Vector2
{
    static const Vector2 kZero;

	float x;
	float y;
};

bool operator==(const Vector2& a, const Vector2& b);

struct Rect
{
	float x;
	float y;
	float width;
	float height;
};
}
