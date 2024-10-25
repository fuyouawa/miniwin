#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class AbstractControl::Impl {
public:
	Impl(AbstractControl* owner);

	void PaintEnd();
	void PaintBegin();

	AbstractControl* owner_;
};
}