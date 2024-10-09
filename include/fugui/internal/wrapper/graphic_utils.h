#pragma once

namespace fugui {
namespace internal {
class GraphicUtils {
public:
	static void* GetCurrentWindow();
	static void EnableWindowTop(void* window, bool b);
};
}
}