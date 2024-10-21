#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class Window : public Widget
{
public:
	Window(std::u8string_view title);
	~Window() override;

    std::u8string_view Title() const;
    void SetTitle(std::u8string_view title) const;

    WindowFlags Flags() const;
    void SetFlags(WindowFlags flags);

	void EnableTop(bool b) const;
	void SetClosable(bool b) const;

	bool IsClosable() const;
	bool IsDocking() const;

protected:
	void PaintBegin() override;
	void PaintEnd() override;

private:
    using Widget::WidgetParent;
    using Widget::SetWidgetParent;

    _MW_IMPL
};
}
