#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class PlatformWindow;
using SharedPlatformWindow = std::shared_ptr<PlatformWindow>;

class Window : public Widget {
	MW_OBJECT
public:
	Window();
	~Window() override;

	String Title() const;
	void SetTitle(const String& title);

	void AlignWindow(Alignment alignment, WindowRelativeTo relative = WindowRelativeTo::kScene);

	bool IsTopEnabled() const;
	bool IsCloseButtonEnabled() const;

	void EnableCloseButton(bool b);
	void EnableTop(bool b);
	void SetCollapsed(bool b);

	Vector2D Pivot() const;
	void SetPivot(Vector2D pivot);

	bool IsDocking() const;
	bool IsCollapsed() const;
	bool IsWindow() const override;

	SharedPlatformWindow PlatformWindow() const;
	void* PlatformHandle() const;
	void SetPlatformWindow(const SharedPlatformWindow& win);

	Vector2D Position(WindowRelativeTo relative = WindowRelativeTo::kScene) const;
	void SetPosition(const Vector2D& pos, WindowRelativeTo relative = WindowRelativeTo::kScene);
	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

	MW_SIGNAL(OnTitleChanged, (String) title, (String) prev_title)
	MW_SIGNAL(OnCollapseChanged, (bool) collapsed)
	MW_SIGNAL(OnDockingChanged)

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	virtual void OnPaintWindowBegin();
	virtual void OnPaintWindowEnd();

private:
	friend class PlatformWindow;
	_MW_IMPL
};
}
