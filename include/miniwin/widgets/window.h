#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(std::u8string_view title);
	~Window() override;

    std::u8string_view Title() const;
    void SetTitle(std::u8string_view title);

	void EnableTop(bool b);
	void SetClosable(bool b);
	void SetCollapsed(bool b);

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
