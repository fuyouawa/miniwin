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
}
