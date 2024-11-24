#include <miniwin/tools/vector2d.h>

#include <miniwin/tools/mathf.h>
#include <type_traits>

namespace miniwin {
namespace internal {
bool EqualFloatingPoint(float x, float y) {
	return Mathf::Approximately(x, y);
}

bool EqualFloatingPoint(double x, double y) {
	return Mathf::Approximately(x, y);
}
}

Vector2DInt VecToVecInt(const Vector2D& v) {
	return { static_cast<int>(v.x()), static_cast<int>(v.y()) };
}

Vector2D VecIntToVec(const Vector2DInt& v) {
	return { static_cast<float>(v.x()), static_cast<float>(v.y()) };
}
}
