#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget {
	MW_OBJECT
public:
	Window();
	~Window() override;

	String Title() const;
	void SetTitle(const String& title);

	/**
	 * 将窗体居中
	 * 注意：居中是相对于主窗体的，不是屏幕
	 */
	void CenterInScene();

	bool IsTopEnabled() const;
	bool IsCloseButtonEnabled() const;

	void EnableCloseButton(bool b);
	void EnableTop(bool b);
	void SetCollapsed(bool b);

	Vector2D CalcSize() const override;
	Vector2D CalcPosition() const override;

	Vector2D Pivot() const;
	void SetPivot(Vector2D pivot);

	bool IsDocking() const;
	bool IsCollapsed() const;

	void* PlatformHandle() const;

	MW_SIGNAL(OnTitleChanged, (String) title, (String) prev_title)
	MW_SIGNAL(OnCollapseChanged, (bool) collapsed)
	MW_SIGNAL(OnDockingChanged)

protected:
	void Awake() override;
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	virtual void OnPaintWindowBegin();
	virtual void OnPaintWindowEnd();

	_MW_IMPL
};
}
