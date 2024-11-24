#pragma once
#include <miniwin/tools/string.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/rect.h>
#include <miniwin/defs.h>

#include <functional>

namespace miniwin {
class EasyWindow;
using SharedEasyWindow = std::shared_ptr<EasyWindow>;
using SharedConstEasyWindow = std::shared_ptr<const EasyWindow>;

class EasyWindow {
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

	virtual ~EasyWindow();

	static SharedEasyWindow Create(
		const String& title,
		const Vector2DInt& size,
		bool client_size = true,
		FlagsType styles = kStyleNormal,
		const SharedEasyWindow& parent = nullptr);

	virtual void Repaint() = 0;
	virtual void Show(bool show_or_hide = true) = 0;
	virtual bool IsFocused() const = 0;
	virtual void SetFocus() = 0;

	virtual void SetSize(const Vector2DInt& size, bool client = true) = 0;
	virtual void SetPosition(const Vector2DInt& pos, bool client = true) = 0;
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

	virtual bool Update() = 0;

	virtual void* PlatformHandle() const = 0;

	std::function<void(Vector2DInt size)> on_resized_;
	std::function<void(Vector2DInt pos)> on_moved_;
	std::function<void(bool force)> on_forced_;
	std::function<bool()> on_close_;
};
}
