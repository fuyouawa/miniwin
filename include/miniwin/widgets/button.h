#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Button : public AbstractControl {
	MW_OBJECT
public:
	Button();
	~Button() override;

	MW_SIGNAL(OnClicked)

protected:
	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
