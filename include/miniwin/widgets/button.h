#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Button : public AbstractTextualControl {
	MW_OBJECT
public:
	Button();
	~Button() override;

	MW_SIGNAL(OnClicked)

protected:
	void PaintBegin() override;

	_MW_IMPL
};
}
