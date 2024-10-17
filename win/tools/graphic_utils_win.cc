#if WIN32
#include "win/tools/graphic_utils.h"
#include <Windows.h>

namespace miniwin {
HWND CastWin(void* window) {
    return reinterpret_cast<HWND>(window);
}

void GraphicUtils::EnableWindowTop(void* window, bool b) {
    ::SetWindowPos(
        CastWin(window),
        HWND_TOPMOST,
        0, 0,
        0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void GraphicUtils::SetWindowSize(void* window, const Vector2Int& size) {
    ::SetWindowPos(
        CastWin(window),
        HWND_TOP,
        0, 0,
        size.x(), size.y(),
        SWP_NOMOVE | SWP_NOZORDER);
}

void GraphicUtils::SetWindowPos(void* window, const Vector2Int& pos) {
    ::SetWindowPos(
        CastWin(window),
        HWND_TOP,
        pos.x(), pos.y(),
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER);
}

RectInt GraphicUtils::GetWindowRect(void* window)
{
    RECT rect;
    ::GetWindowRect(CastWin(window), &rect);
    return {
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top
    };
}
}
#endif // WIN32
