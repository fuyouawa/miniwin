#pragma once
#include <miniwin/global/defs.h>

#include <miniwin/tools/vector2d.h>

namespace miniwin {
namespace io {
bool IsIoKeyDown(IoKeyCode kc);
bool IsKeyDown(KeyCode kc);
bool IsKeyPressed(KeyCode kc, bool repeat = true);
bool IsKeyReleased(KeyCode kc);

bool IsMouseDown(MouseButton button);
bool IsMouseClicked(MouseButton button);
bool IsMouseReleased(MouseButton button);
bool IsMouseDoubleClicked(MouseButton button);

Vector2D GetMousePos();
Vector2D DisplaySize();
}
}
