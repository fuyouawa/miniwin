#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Frame : public AbstractMinimumControl {
	MW_OBJECT
public:
	Frame();

protected:
	void PaintBegin() override;
	void PaintEnd() override;

	_MW_IMPL
};
}
