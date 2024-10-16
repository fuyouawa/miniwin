#include <format>
#include <miniwin/core/widget.h>
#include <miniwin/tools/container.h>
#include <miniwin/tools/scope_variable.h>

#include <win/core/widget_impl.h>

#include "widgets_driver.h"

namespace miniwin {
WidgetFlags operator|(WidgetFlags x, WidgetFlags y)
{
    return static_cast<WidgetFlags>(static_cast<int>(x) | static_cast<int>(y));
}

WidgetFlags operator&(WidgetFlags x, WidgetFlags y)
{
    return static_cast<WidgetFlags>(static_cast<int>(x) & static_cast<int>(y));
}

Widget::Widget(Widget* parent, std::u8string_view name, WidgetType widget_type)
    : Object(parent, name, ObjectType::Widget)
{
    impl_ = std::make_unique<Impl>(this, widget_type);
    impl_->widget_type_ = widget_type;
}

Widget::~Widget()
{
}

void Widget::Close()
{
    impl_->Close();
}

const Widget* Widget::GetWidgetParent() const
{
    return impl_->widget_parent();
}

void Widget::SetWidgetParent(Widget* parent) const
{
    impl_->set_widget_parent(parent);
}

const std::vector<Widget*>& Widget::GetWidgetChildren() const
{
    return impl_->widget_children_;
}

void Widget::SetEnable(bool b) const { impl_->set_enable(b); }


Vector2 Widget::size() const {
    return impl_->size_sc_.get();
}

void Widget::set_size(const Vector2& size) const {
    impl_->size_sc_.set_control(size);
}

bool Widget::orphaned() const
{
    return impl_->orphaned_;
}

bool Widget::GetEnabled() const { return impl_->enabled(); }

bool Widget::GetVisible() const {
    return impl_->visible();
}

void Widget::SetVisible(bool b) const
{
    impl_->set_visible(b);
}

WidgetType Widget::widget_type() const {
    return impl_->widget_type_;
}

WidgetFlags Widget::widget_flags() const
{
    return impl_->widget_flags_;
}

void Widget::set_widget_flags(WidgetFlags widget_flags)
{
    impl_->widget_flags_ = widget_flags;
}

void Widget::Invoke(std::function<void()>&& func, InvokeType invoke_type) const
{
    if (IsInUIThread())
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
    return std::this_thread::get_id() == WidgetsDriver::instance().ui_thread_id();
}

// void Widget::Invoke(Functor&& func, InvokeType type) const {
//     switch (type)
//     {
//     case InvokeType::kAuto:
//         if (IsInOwnerThread()) {
//             Invoke(std::move(func), InvokeType::kDirect);
//         }
//         else {
//             Invoke(std::move(func), InvokeType::kQueued);
//         }
//         break;
//     case InvokeType::kDirect:
//         func();
//         break;
//     case InvokeType::kQueued:
//         internal::WidgetEngine::instance().InvokeInNextFrame(std::move(func));
//         break;
//     default:
//         assert(false);
//         break;
//     }
// }

void Widget::UpdateEarly()
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
