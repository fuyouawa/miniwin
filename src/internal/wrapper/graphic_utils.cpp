#include <fugui/internal/wrapper/graphic_utils.h>
#include <imgui/imgui.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui_internal.h>

namespace fugui {
namespace internal {
GLFWwindow* CastWin(void* window) {
	return reinterpret_cast<GLFWwindow*>(window);
}

void* GraphicUtils::GetCurrentWindow() {
	return ImGui::GetWindowViewport()->PlatformHandle;
}

void GraphicUtils::EnableWindowTop(void* window, bool b) {
	glfwSetWindowAttrib(CastWin(window), GLFW_FLOATING, b);
}
}
}