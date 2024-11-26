#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Frame : public AbstractControl {
	MW_OBJECT
public:
	Frame();

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void BeginUpdate(size_t index) override;
	void EndUpdate(size_t index) override;

	_MW_IMPL
};
}
