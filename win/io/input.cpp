#include <miniwin/io/input.h>
#include <imgui/imgui.h>

namespace miniwin {
bool Input::IsIoKeyDown(IoKeyCode kc)
{
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case miniwin::IoKeyCode::kCtrl:
		return io.KeyCtrl;
	default:
		assert(false);
		return false;
	}
}
}