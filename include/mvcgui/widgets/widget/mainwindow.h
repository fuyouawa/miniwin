#pragma once
#include <mvcgui/widgets/widget/window.h>

namespace mvcgui {
class MainWindow : public Window {
public:
	MainWindow(std::u8string_view title, bool show = true);

protected:
	void OnPaintBegin() override;
	void OnPaintEnd() override;

private:
	Widget* parent() const override { assert(false); return nullptr; }
	void set_parent(Widget* parent) override { assert(false); }
};
}