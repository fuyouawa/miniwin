#pragma once
#include <miniwin/widgets/layout/layout.h>

namespace miniwin {
class BoxLayout : public Layout {
public:
	BoxLayout(Widget* parent);
	~BoxLayout() override;

	float Spacing() const;
	void SetSpacing(float size);

	_MW_IMPL
};

class HBoxLayout : public BoxLayout
{
public:
	HBoxLayout(Widget* parent);

protected:
	void OnBeforePaintChild(size_t child_index) override;
};

class VBoxLayout : public BoxLayout
{
public:
	VBoxLayout(Widget* parent);

protected:
	void OnBeforePaintChild(size_t child_index) override;
};
}