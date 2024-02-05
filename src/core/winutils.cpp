#include <mvcgui/core/winutils.h>
#include <imgui/imgui.h>

namespace mvcgui {
bool WinUtils::IsWindowDocked() {
	return ImGui::IsWindowDocked();
}
}