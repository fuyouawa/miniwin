#include <mvcgui/io/input.h>
#include <imgui/imgui.h>

namespace mvcgui {
bool Input::GetKeyDown(KeyCode kc)
{
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case mvcgui::KeyCode::kCtrl:
		return io.KeyCtrl;
		break;
	default:
		assert(false);
		return false;
	}
}
}