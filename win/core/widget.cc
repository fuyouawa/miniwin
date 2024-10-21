#include <format>
#include <miniwin/core/widget.h>
#include <miniwin/tools/container.h>
#include <miniwin/tools/scope_variable.h>

#include <win/core/widget_impl.h>

#include "widgets_driver.h"

namespace miniwin {
Widget::Widget(Widget* parent, std::u8string_view name)
    : Object(parent, name)
{
    impl_ = std::make_unique<Impl>(this);
}

Widget::~Widget()
{
}

void Widget::Close()
{
    impl_->Close();
}

const Widget* Widget::WidgetParent() const
{
    return impl_->WidgetParent();
}

void Widget::SetWidgetParent(Widget* parent) const
{
    impl_->SetWidgetParent(parent);
}

const std::vector<Widget*>& Widget::WidgetChildren() const
{
    return impl_->widget_children_;
}

void Widget::SetEnable(bool b) const { impl_->SetEnable(b); }


Vector2 Widget::Size() const {
    return impl_->size_sc_.get();
}

void Widget::SetSize(const Vector2& size) const {
    impl_->size_sc_.set_control(size);
}

bool Widget::Orphaned() const
{
    return impl_->orphaned_;
}

bool Widget::Enabled() const { return impl_->Enabled(); }

bool Widget::Visible() const {
    return impl_->Visible();
}

void Widget::SetVisible(bool b) const
{
    impl_->SetVisible(b);
}

WidgetDrawFlags Widget::DrawFlags() const
{
    return impl_->draw_flags_;
}

void Widget::SetDrawFlags(WidgetDrawFlags draw_flags)
{
    impl_->draw_flags_ = draw_flags;
}

void Widget::Invoke(std::function<void()>&& func, InvokeType invoke_type) const
{
    if (IsInUIThread() && invoke_type == InvokeType::kAuto)
    {
        invoke_type = InvokeType::kDirect;
    }
    else
    {
        invoke_type = invoke_type == InvokeType::kAuto ? InvokeType::kQueued : invoke_type;
    }

    switch (invoke_type)
    {
    case InvokeType::kDirect:
        func();
        break;
    case InvokeType::kQueued:
        impl_->PushPendingFunctor(std::move(func));
        break;
    default:
        assert(invoke_type == InvokeType::kDirect || invoke_type == InvokeType::kQueued);
        break;
    }
}

bool Widget::IsInUIThread()
{
    return std::this_thread::get_id() == WidgetsDriver::instance().UiThreadId();
}

void Widget::PreparePaint()
{
    impl_->DoPendingFunctors();
}

void Widget::PaintBegin()
{
    impl_->PaintBegin();
}

void Widget::PaintEnd()
{
    impl_->PaintEnd();
}
}
