#include "abstract_control_impl.h"

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
AbstractControl::AbstractControl(Widget* parent, std::u8string_view text)
	: Widget{ parent, text }
{
    impl_ = std::make_unique<Impl>(this);
}

AbstractControl::~AbstractControl()
{
}

std::u8string_view AbstractControl::Text() const
{
    return Name();
}

void AbstractControl::SetText(std::u8string_view text)
{
    SetName(text);
}

bool AbstractControl::Visible() const
{
    //TODO ImGui::GetCurrentWindow
    return Widget::Visible() && !ImGui::GetCurrentWindow()->SkipItems;
}

void AbstractControl::PaintBegin()
{
	Widget::PaintBegin();
    impl_->PaintBegin();
}

void AbstractControl::PaintEnd()
{
    Widget::SetSize(ImGuiHelper::GetItemRectSize());
    impl_->PaintEnd();
	Widget::PaintEnd();
}
}
