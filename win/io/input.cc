#include <miniwin/io/input.h>

#include <imgui/imgui.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace io {
bool IsKeyDown(KeyCode kc) {
	auto& io = ImGui::GetIO();
	switch (kc)
	{
	case KeyCode::kCtrl:
		return io.KeyCtrl;
	default:
		MW_ASSERT_X(false);
		return false;
	}
}
}
}
