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

	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;

	virtual Vector2D RelativePosition() const;
	virtual void SetRelativePosition(const Vector2D& pos);
	void SetRelativePositionX(float x);
	void SetRelativePositionY(float y);

protected:
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}
