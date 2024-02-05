#include <mvcgui/io/input.h>
#include <imgui/imgui.h>

namespace mvcgui {
bool Input::IsIoKeyDown(IoKeyCode kc)
{
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case mvcgui::IoKeyCode::kCtrl:
		return io.KeyCtrl;
	default:
		assert(false);
		return false;
	}
}
}