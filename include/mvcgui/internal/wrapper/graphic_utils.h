#pragma once

namespace mvcgui {
namespace internal {
class GraphicUtils {
public:
	static void* GetCurrentWindow();
	static void SetWindowTop(void* window, bool b);
};
}
}