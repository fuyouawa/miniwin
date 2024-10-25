#include <miniwin/tools/vector2d.h>

#include <miniwin/tools/mathf.h>

namespace miniwin {
bool operator==(const Vector2D& a, const Vector2D& b) {
	return Mathf::Approximately(a.x(), a.x()) && Mathf::Approximately(a.y(), a.y());
}

bool operator==(const Vector2DInt& a, const Vector2DInt& b)
{
    return a.x() == b.x() && a.y() == b.y();
}
}
