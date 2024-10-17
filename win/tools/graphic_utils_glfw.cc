#ifndef WIN32
#include "win/tools/graphic_utils.h"
#include <GLFW/glfw3.h>

namespace miniwin {
GLFWwindow* CastWin(void* window) {
    return reinterpret_cast<GLFWwindow*>(window);
}

void GraphicUtils::EnableWindowTop(void* window, bool b) {
    glfwSetWindowAttrib(CastWin(window), GLFW_FLOATING, b);
}
}
#endif // !WIN32
