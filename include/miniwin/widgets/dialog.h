#pragma once
#include <miniwin/widgets/window.h>

namespace miniwin {
class Dialog : public Window
{
public:
	Dialog(Widget* parent = nullptr, const String& title = "Dialog", const String& id = "Dialog");
	~Dialog() override;

	void Open();

protected:
	void OnPaintWindowBegin() override;
	void OnPaintWindowEnd() override;

	_MW_IMPL
};
}