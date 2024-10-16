#include <miniwin/tools/container.h>
#include <miniwin/tools/mathf.h>

namespace miniwin {
const Vector2 Vector2::kZero{ 0, 0 };

bool operator==(const Vector2& a, const Vector2& b) {
	return Mathf::Approximately(a.x, a.x) && Mathf::Approximately(a.y, a.y);
}
}
