#include <miniwin/tools/container.h>
#include <miniwin/tools/mathf.h>

namespace miniwin {
bool operator==(const Vector2& a, const Vector2& b) {
	return Mathf::Approximately(a.x(), a.x()) && Mathf::Approximately(a.y(), a.y());
}

bool operator==(const Vector2Int& a, const Vector2Int& b)
{
    return a.x() == b.x() && a.y() == b.y();
}
}
