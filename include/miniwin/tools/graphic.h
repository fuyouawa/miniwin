#pragma once
#include <optional>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/rect.h>

namespace miniwin {
namespace graphic {
void* GetCurrentWindow();

bool EnableWindowTop(void* window, bool b);

bool SetWindowSize(void* window, const Vector2DInt& size);
bool SetWindowPos(void* window, const Vector2DInt& pos);
std::optional<Rect> GetWindowRect(void* window);

Vector2D GetSceneSize();
}
}
