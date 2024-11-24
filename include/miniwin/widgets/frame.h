#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Frame : public AbstractMinimumControl {
	MW_OBJECT
public:
	Frame();

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}
