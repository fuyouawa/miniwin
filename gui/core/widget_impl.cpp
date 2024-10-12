#include "gui/core/widget_impl.h"
#include "imgui/imgui.h"

namespace fugui {
Widget::Impl::Impl(Widget* owner)
    : enable_sc_(true),
    visible_sc_(true),
    is_painting_children_(false),
    flags_(0), widget_type_(), owner_(owner)
{
}

Widget::Impl::~Impl()
{
}

void Widget::Impl::PaintBegin()
{
    enable_sc_.Entry();
    visible_sc_.Entry();

    if (enable_sc_.is_changed()) {
        owner_->OnEnableChanged(*enable_sc_);
        owner_->DoEnable(*enable_sc_);
    }

    if (visible_sc_.is_changed()) {
        if (*visible_sc_) {
            owner_->DoShow();
        }
        else {
            owner_->DoHide();
        }
        owner_->OnVisbleChanged(*visible_sc_);
    }
    if (!*enable_sc_) {
        ImGui::BeginDisabled();
    }
}

void Widget::Impl::PaintEnd()
{
    if (!*enable_sc_) {
        ImGui::EndDisabled();
    }

    enable_sc_.Exit();
    visible_sc_.Exit();
}

bool Widget::Impl::visible() const
{
    auto v = visible_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->parent_widget();
    if (!p)
    {
        return v;
    }
    return p->visible();
}

void Widget::Impl::set_visible(bool b)
{
    visible_sc_.set_control(b);
}

bool Widget::Impl::enabled() const
{
    auto v = enable_sc_.get();
    if (!v)
    {
        return false;
    }
    auto p = owner_->parent_widget();
    if (!p)
    {
        return v;
    }
    return p->enabled();
}

void Widget::Impl::set_enable(bool b)
{
    enable_sc_.set_control(b);
}
}
