#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
//TODO CheckBox只计算文本大小，按钮的宽度没算在内
class CheckBox : public AbstractControl {
	MW_OBJECT
public:
	CheckBox();
	~CheckBox() override;

	void SetChecked(bool b);

	MW_SIGNAL(OnToggled, (bool) checked)

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

private:
	void SetSize(const Vector2D& size) override;

	_MW_IMPL
};

}
