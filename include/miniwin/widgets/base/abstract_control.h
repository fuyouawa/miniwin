#pragma once
#include <miniwin/core/widget.h>

namespace miniwin {
class AbstractControl : public Widget {
	MW_OBJECT
public:
	AbstractControl();
	~AbstractControl() override;

	bool Visible() const override;
	bool IsControl() const override;

	Vector2D Position(ControlRelativeTo relative = ControlRelativeTo::kWindow) const;
	void SetPosition(const Vector2D& pos, ControlRelativeTo relative = ControlRelativeTo::kWindow);

protected:
	void BeginUpdate(size_t index) override;
	void EndUpdate(size_t index) override;

	_MW_IMPL
};
}
