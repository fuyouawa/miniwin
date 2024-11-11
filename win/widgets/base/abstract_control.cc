#include "abstract_control_impl.h"

#include <imgui/imgui_internal.h>
#include <miniwin/core/imgui.h>

namespace miniwin {
AbstractControl::AbstractControl(Widget* parent, const String& text)
	: Widget{ parent, text }
{
    impl_ = std::make_unique<Impl>(this);
}

AbstractControl::~AbstractControl()
{
}

const String& AbstractControl::Text() const
{
    return Name();
}

void AbstractControl::SetText(const String& text)
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
    Widget::SetSize(imgui::GetItemRectSize());
    impl_->PaintEnd();
	Widget::PaintEnd();
}
}
