#pragma once
#include <miniwin/tools/vector2d.h>
#include <miniwin/defs.h>
#include <imgui/imgui.h>

namespace miniwin {
ImVec2 CastToIm(const Vector2D& vec);

Vector2D CastFromIm(const ImVec2& vec);

ImGuiMouseButton_ CastToIm(MouseButton button);
}
