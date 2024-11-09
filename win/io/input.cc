#include <miniwin/io/input.h>

#include <imgui/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
bool Input::IsIoKeyDown(IoKeyCode kc)
{
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case IoKeyCode::kCtrl:
		return io.KeyCtrl;
	default:
		MW_ASSERT_X(false);
		return false;
	}
}
}
