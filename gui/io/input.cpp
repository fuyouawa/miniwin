#include <fugui/io/input.h>
#include <imgui/imgui.h>

namespace fugui {
bool Input::IsIoKeyDown(IoKeyCode kc)
{
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case fugui::IoKeyCode::kCtrl:
		return io.KeyCtrl;
	default:
		assert(false);
		return false;
	}
}
}