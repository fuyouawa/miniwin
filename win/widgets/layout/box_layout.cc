#include "box_layout_impl.h"

#include <miniwin/core/imgui.h>

namespace miniwin {
BoxLayout::BoxLayout(Widget* parent)
	: Layout(parent)
{
	impl_ = std::make_unique<Impl>(this);
}

BoxLayout::~BoxLayout()
{
}

float BoxLayout::Spacing() const
{
	return impl_->spacing_;
}

void BoxLayout::SetSpacing(float size)
{
	impl_->spacing_ = size;
}

HBoxLayout::HBoxLayout(Widget* parent)
	: BoxLayout(parent)
{
}

void HBoxLayout::OnBeforePaintChild(size_t child_index)
{
	BoxLayout::OnBeforePaintChild(child_index);
	if (child_index != 0)
	{
		imgui::SameLine(0, Spacing());
	}
}

VBoxLayout::VBoxLayout(Widget* parent)
	: BoxLayout(parent)
{
}

void VBoxLayout::OnBeforePaintChild(size_t child_index)
{
	BoxLayout::OnBeforePaintChild(child_index);

	if (child_index != 0)
	{
		imgui::Dummy({ 0, Spacing() });
	}
}
}
