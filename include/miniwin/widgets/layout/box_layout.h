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

	float Alignment() const;
	void SetAlignment(float alignment);

	float AdditionSpacing(const SharedWidget& widget) const;
	void SetAdditionSpacing(const SharedWidget& widget, float spacing);

	_MW_IMPL
};

class HBoxLayout : public BoxLayout {
	MW_OBJECT
public:
	HBoxLayout();

	float TotalWidth() const;

protected:
	void OnBeginLayout() override;
	void OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) override;
};

class VBoxLayout : public BoxLayout {
	MW_OBJECT
public:
	VBoxLayout();

	float TotalHeight() const;

protected:
	void OnLayoutWidgetBegin(const SharedWidget& widget, size_t index) override;
};
}
