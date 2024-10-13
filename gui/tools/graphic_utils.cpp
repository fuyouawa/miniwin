#include <gui/tools/graphic_utils.h>
#include <imgui/imgui.h>
#include <GLFW/glfw3.h>

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

void GraphicUtils::SetWindowSize(void* window, int width, int height)
{
	glfwSetWindowSize(CastWin(window), width, height);
}

void GraphicUtils::GetWindowSize(void* window, int* width, int* height)
{
	glfwGetWindowSize(CastWin(window), width, height);
}

void GraphicUtils::SetWindowPos(void* window, int x, int y)
{
	glfwSetWindowPos(CastWin(window), x, y);
}
}
}
