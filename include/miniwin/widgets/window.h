#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(Widget* parent = nullptr, const String& title = "Window", const String& id = "Window");
	~Window() override;

    const String& Title() const;
    void SetTitle(const String& title);
	void SetId(const String& id) override;

	/**
	 * 将窗体居中
	 * 注意：居中是相对于主窗体的，不是屏幕
	 */
	void CenterWindow();

	bool IsTopEnabled() const;
	bool IsCloseButtonEnabled() const;

	void EnableCloseButton(bool b);
	void EnableTop(bool b);
	void SetCollapsed(bool b);

	void SetSize(const Vector2D& size) override;
	void SetPosition(const Vector2D& pos) override;
	void SetPosition(const Vector2D& pos, const Vector2D& pivot);

	bool IsDocking() const;
	bool IsCollapsed() const;

	void* PlatformHandle() const;

	MW_SIGNAL(OnTitleChanged, (String) title, (String) prev_title)
	MW_SIGNAL(OnCollapseChanged, (bool) collapsed)
	MW_SIGNAL(OnDockingChanged)

protected:
	void PaintBegin() override;
	void PaintEnd() override;

	virtual void OnPaintWindowBegin();
	virtual void OnPaintWindowEnd();

    _MW_IMPL
};
}
