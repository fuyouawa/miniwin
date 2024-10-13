#pragma once

namespace miniwin {
namespace internal {
class GraphicUtils {
public:
	static void* GetCurrentWindow();
	static void EnableWindowTop(void* window, bool b);
	static void SetWindowSize(void* window, int width, int height);
	static void GetWindowSize(void* window, int* width, int* height);
	static void SetWindowPos(void* window, int x, int y);
};
}
}
