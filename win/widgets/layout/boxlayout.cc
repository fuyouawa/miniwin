#include "boxlayout_impl.h"

#include <miniwin/core/imgui_helper.h>

namespace miniwin {
BoxLayout::BoxLayout(Widget* parent)
	: Layout(parent)
{
	impl_ = std::make_unique<Impl>(this);
}

BoxLayout::~BoxLayout()
{
}

size_t BoxLayout::Spacing() const
{
	return impl_->spacing_;
}

void BoxLayout::SetSpacing(size_t size)
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
		ImGuiHelper::SameLine(0, Spacing());
	}
}
}
