#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractControl {
	MW_OBJECT
public:
	Label();

protected:
	void PaintBegin(size_t index) override;

private:
	void SetSize(const Vector2D& size) override;
};
}
