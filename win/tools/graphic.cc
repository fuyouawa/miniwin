#include <miniwin/tools/graphic.h>

#include <imgui/imgui.h>

namespace miniwin {
namespace graphic {
void* GetCurrentWindow() {
    return ImGui::GetWindowViewport()->PlatformHandle;
}
}
}
