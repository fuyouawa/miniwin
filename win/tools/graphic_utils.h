#pragma once
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/rect.h>

namespace miniwin {
class GraphicUtils {
public:
	static void* GetCurrentWindow();

	static void EnableWindowTop(void* window, bool b);

	static void SetWindowSize(void* window, const Vector2DInt& size);
    static void SetWindowPos(void* window, const Vector2DInt& pos);
	static RectInt GetWindowRect(void* window);
};
}
