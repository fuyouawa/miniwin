#include <miniwin/io/scene.h>
#include <imgui/imgui.h>

namespace miniwin {
namespace io {
Vector2D DisplaySize()
{
	auto& io = ImGui::GetIO();
	return { io.DisplaySize.x, io.DisplaySize.y };
}
}
}