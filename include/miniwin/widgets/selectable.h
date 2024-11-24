#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class Selectable : public AbstractControl {
	MW_OBJECT
public:
	Selectable();
	~Selectable() override;

	bool IsSelected() const;
	void SetSelection(bool b);

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

	void SetText(const String& text, bool adjust_size = true) override;

	MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
	void Start() override;
	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
