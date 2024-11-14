#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Frame : public AbstractControl {
public:
	Frame(Widget* parent);

protected:
	void PaintBegin() override;
	void PaintEnd() override;

	_MW_IMPL
};
}
