#include <fugui/tools/container.h>

namespace fugui {
Vector2 Vector2::Zero{0, 0};

bool operator==(const Vector2& x, const Vector2& y) {
	return x.x == y.x && x.y == y.y;
}
}