#pragma once
#include <miniwin/tools/container.h>

namespace miniwin {
class GraphicUtils {
public:
	static void* GetCurrentWindow();

	static void EnableWindowTop(void* window, bool b);

	static void SetWindowSize(void* window, const Vector2Int& size);
    static void SetWindowPos(void* window, const Vector2Int& pos);
	static RectInt GetWindowRect(void* window);
};
}
