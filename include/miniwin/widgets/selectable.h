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

	MW_SIGNAL(OnSelectionChanged, (bool) selected)

protected:
	void PaintBegin() override;

	_MW_IMPL
};
}
