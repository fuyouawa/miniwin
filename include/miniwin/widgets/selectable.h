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

	String Text() const;
	void SetText(const String& text, bool adjust_size = true);

	MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
	void Start() override;
	void BeginUpdate(size_t index) override;

	_MW_IMPL
};
}
