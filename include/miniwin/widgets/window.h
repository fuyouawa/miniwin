#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class MainWindow;
using SharedMainWindow = std::shared_ptr<MainWindow>;

class Window : public Widget {
	MW_OBJECT
public:
	enum CenterRelative {
		kCenterRelativeToMainWindow,
		kCenterRelativeToScene
	};
	Window();
	~Window() override;

	String Title() const;
	void SetTitle(const String& title);

	SharedMainWindow OwnerMainWindow() const;
	void SetMainWindow(const SharedMainWindow& win);

	/**
	 * 将窗体居中
	 */
	void AlignCenter(CenterRelative relative = kCenterRelativeToMainWindow);

	bool IsTopEnabled() const;
	bool IsCloseButtonEnabled() const;

	void EnableCloseButton(bool b);
	void EnableTop(bool b);
	void SetCollapsed(bool b);

	Vector2D Pivot() const;
	void SetPivot(Vector2D pivot);

	bool IsDocking() const;
	bool IsCollapsed() const;

	void* PlatformHandle() const;

	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;
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
	friend class MainWindow;
	_MW_IMPL
};
}
