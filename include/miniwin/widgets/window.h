#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(const String& title);
	~Window() override;

    const String& Title() const;
    void SetTitle(const String& title);

	/**
	 * 将窗体居中
	 * 注意：居中是相对于主窗体的，不是屏幕
	 */
	void CenterWindow();

	void EnableTop(bool b);
	void SetClosable(bool b);
	void SetCollapsed(bool b);

	void SetSize(const Vector2D& size) override;
	void SetPosition(const Vector2D& pos) override;
	void SetPosition(const Vector2D& pos, const Vector2D& pivot);

	bool IsClosable() const;
	bool IsDocking() const;
	bool IsCollapsed() const;

	MW_SIGNAL(OnCollapseChanged, (bool) collapsed)
	MW_SIGNAL(OnDockingChanged)

protected:
	void PaintBegin() override;
	void PaintEnd() override;

private:
    using Widget::WidgetParent;
    using Widget::SetWidgetParent;

    _MW_IMPL
};
}
