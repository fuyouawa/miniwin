#pragma once
#include <miniwin/core/objectdefs.h>
#include <miniwin/tools/string.h>
#include <miniwin/tools/vector2d.h>

#include <thread>

namespace miniwin {
class PlatformWindow;
using SharedPlatformWindow = std::shared_ptr<PlatformWindow>;

class PlatformWindow : public std::enable_shared_from_this<PlatformWindow> {
public:
	enum StyleFlags : uint8_t {
		kStyleNormal,
		kStyleBorderless,
		kStyleResizable,
		kStylePopup
	};

	enum CursorType : uint8_t {
		kCursorNone,
		kCursorArrow,
		kCursorTextInput,
		kCursorHand,
		kCursorResizeNS,
		kCursorResizeEW,
		kCursorResizeNESW
	};

	static SharedPlatformWindow Create(
		const String& title,
		const Vector2DInt& size,
		bool adjust_size = true, 
		FlagsType styles = kStyleNormal, 
		const SharedPlatformWindow& parent = nullptr);

	virtual ~PlatformWindow();

	virtual void Repaint() = 0;
	virtual void Show(bool show_or_hide = true) = 0;
	virtual bool IsFocused() const = 0;
	virtual void SetFocus() = 0;

	virtual void SetSize(const Vector2DInt& size, bool adjust = true) = 0;
	virtual void SetPosition(const Vector2DInt& pos, bool adjust = true) = 0;
	virtual void SetMaximized(bool b) = 0;
	virtual void SetMinimized(bool b) = 0;
	virtual void SetTitle(const String& title) = 0;
	virtual void SetAlpha(uint8_t alpha) = 0;
	virtual void SetCursor(CursorType cursor) = 0;

	virtual Vector2DInt ClientSize() const = 0;
	virtual Vector2DInt Size() const = 0;
	virtual Vector2DInt ClientPosition() const = 0;
	virtual Vector2DInt Position() const = 0;

	virtual bool IsMaximized() const = 0;
	virtual bool IsMinimized() const = 0;

	virtual uint64_t FrameCount() const = 0;

	virtual bool IsDone() const = 0;
	virtual bool Update() = 0;
	virtual bool IsUpdated() = 0;

	virtual void* PlatformHandle() const = 0;

	virtual const List<SharedWindow>& SubWindows() = 0;
};
}
