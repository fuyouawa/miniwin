#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Frame : public AbstractMinimumControl {
	MW_OBJECT
public:
	Frame();

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}
