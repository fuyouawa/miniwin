#if WIN32
#include <miniwin/tools/graphic.h>

#include <Windows.h>

namespace miniwin {
namespace graphic {
HWND CastWin(void* window) {
    return reinterpret_cast<HWND>(window);
}

bool EnableWindowTop(void* window, bool b) {
    return ::SetWindowPos(
        CastWin(window),
        b ? HWND_TOPMOST : HWND_NOTOPMOST,
        0, 0,
        0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

bool SetWindowSize(void* window, const Vector2DInt& size) {
    return ::SetWindowPos(
        CastWin(window),
        HWND_TOP,
        0, 0,
        size.x(), size.y(),
        SWP_NOMOVE | SWP_NOZORDER);
}

bool SetWindowPos(void* window, const Vector2DInt& pos) {
    return ::SetWindowPos(
        CastWin(window),
        HWND_TOP,
        pos.x(), pos.y(),
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER);
}

std::optional<Rect> GetWindowRect(void* window)
{
    RECT rect;
    if (!::GetWindowRect(CastWin(window), &rect)) {
        return std::nullopt;
    }
    return Rect(
        static_cast<float>(rect.left),
        static_cast<float>(rect.top),
        static_cast<float>(rect.right - rect.left),
        static_cast<float>(rect.bottom - rect.top));
}

Vector2D GetSceneSize() {
    return {
    	static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
    	static_cast<float>(GetSystemMetrics(SM_CYSCREEN)) };
}
}
}
#endif // WIN32
