#include <miniwin/core/io.h>

#include <imgui/imgui.h>

#include "win/tools/debug.h"
#include "win/core/imgui_cast.h"

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
	return ImGui::IsKeyDown(static_cast<ImGuiKey>(kc));
}

bool IsKeyPressed(KeyCode kc, bool repeat) {
	return ImGui::IsKeyPressed(static_cast<ImGuiKey>(kc), repeat);
}

bool IsKeyReleased(KeyCode kc) {
	return ImGui::IsKeyReleased(static_cast<ImGuiKey>(kc));
}

bool IsMouseDown(MouseButton button) {
	return ImGui::IsMouseDown(CastToIm(button));
}

bool IsMouseClicked(MouseButton button) {
	return ImGui::IsMouseClicked(CastToIm(button));
}

bool IsMouseReleased(MouseButton button) {
	return ImGui::IsMouseReleased(CastToIm(button));
}

bool IsMouseDoubleClicked(MouseButton button) {
	return ImGui::IsMouseDoubleClicked(CastToIm(button));
}

Vector2D GetMousePos() {
	return CastFromIm(ImGui::GetMousePos());
}

Vector2D DisplaySize()
{
	auto& io = ImGui::GetIO();
	return { io.DisplaySize.x, io.DisplaySize.y };
}
}
}
