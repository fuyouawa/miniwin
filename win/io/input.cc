#include <miniwin/io/input.h>

#include <imgui/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace io {
bool IsIoKeyDown(IoKeyCode kc) {
	auto& io = ImGui::GetIO();
	switch (kc) {
	case IoKeyCode::kCtrl:
		return io.KeyCtrl;
	case IoKeyCode::kAlt:
		return io.KeyAlt;
	case IoKeyCode::kShift:
		return io.KeyShift;
	case IoKeyCode::kSuper:
		return io.KeySuper;
	default:
		break;
	}
	return false;
}

bool IsKeyDown(KeyCode kc) {
	MW_ASSERT_X(static_cast<uint32_t>(kc) < ImGuiKey_COUNT);
	auto& io = ImGui::GetIO();
	return io.KeysDown[static_cast<uint32_t>(kc)];
}
}
}
