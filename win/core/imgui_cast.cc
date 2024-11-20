#include "imgui_cast.h"

#include "win/tools/debug.h"

namespace miniwin {
ImVec2 CastToIm(const Vector2D& vec) {
	return { vec.x(), vec.y() };
}

Vector2D CastFromIm(const ImVec2& vec) {
	return { vec.x, vec.y };
}

ImGuiMouseButton_ CastToIm(MouseButton button) {
	switch (button) {
	case MouseButton::kLeft: return ImGuiMouseButton_Left;
	case MouseButton::kRight: return ImGuiMouseButton_Right;
	case MouseButton::kMiddle: return ImGuiMouseButton_Middle;
	default:
		MW_ASSERT_X(false);
		return ImGuiMouseButton_COUNT;
	}
}
}
