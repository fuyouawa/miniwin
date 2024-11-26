#pragma once
#include <miniwin/widgets/window.h>

namespace miniwin {
class Dialog : public Window {
	MW_OBJECT
public:
	Dialog();
	~Dialog() override;

protected:
	void OnPaintWindowBegin() override;
	void OnPaintWindowEnd() override;

	_MW_IMPL
};
}
