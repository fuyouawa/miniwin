#include <win/tools/graphic_utils.h>

#include <imgui/imgui.h>

namespace miniwin {
void* GraphicUtils::GetCurrentWindow() {
    return ImGui::GetWindowViewport()->PlatformHandle;
}
}
