#pragma once
#include <miniwin/widgets/layout/layout.h>

namespace miniwin {
class BoxLayout : public Layout {
	MW_OBJECT
public:
	BoxLayout();
	~BoxLayout() override;

	float Spacing() const;
	void SetSpacing(float size);

	_MW_IMPL
};

class HBoxLayout : public BoxLayout {
	MW_OBJECT
public:
	HBoxLayout();

protected:
	void OnLayoutWidgetBegin(const SharedWidget& widget) override;
};

class VBoxLayout : public BoxLayout {
	MW_OBJECT
public:
	VBoxLayout();

protected:
	void OnLayoutWidgetBegin(const SharedWidget& widget) override;
};
}
