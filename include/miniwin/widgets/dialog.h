#pragma once
#include <miniwin/widgets/window.h>

namespace miniwin {
class Dialog : public Window
{
public:
	Dialog(Widget* parent);
	~Dialog() override;

	_MW_IMPL
};
}