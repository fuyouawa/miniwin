#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Label : public AbstractControl {
	MW_OBJECT
public:
	Label();
	~Label() override;

	void SetText(const String& text, bool adjust_size = true) override;

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Start() override;
	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
