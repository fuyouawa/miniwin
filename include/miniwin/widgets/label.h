#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractTextualControl {
	MW_OBJECT
public:
	Label();

protected:
	void PaintBegin() override;

private:
	void SetSize(const Vector2D& size) override;
};
}
