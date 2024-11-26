#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Button : public AbstractControl {
	MW_OBJECT
public:
	Button();
	~Button() override;

	String Text() const;
	void SetText(const String& text, bool adjust_size = true);
	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

	MW_SIGNAL(OnClicked)

protected:
	void Start() override;
	void BeginUpdate(size_t index) override;
	void EndUpdate(size_t index) override;

	_MW_IMPL
};
}
