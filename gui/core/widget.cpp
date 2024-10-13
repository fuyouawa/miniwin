#include <format>
#include <fugui/core/widget.h>
#include <fugui/tools/container.h>
#include <fugui/tools/scope_variable.h>

#include <gui/core/widget_impl.h>

#include "widgets_driver.h"

namespace fugui {
Widget::Widget(Widget* parent, std::u8string_view name, bool show, WidgetType widget_type)
    : Object(parent, name)
{
    impl_ = std::make_unique<Impl>(this);
    impl_->widget_type_ = widget_type;
    impl_->set_visible(show);
}

Widget::~Widget()
{
}

void Widget::Show() {
    impl_->set_visible(true);
}

void Widget::Close()
{
    impl_->Close();
}

void Widget::Hide() {
    impl_->set_visible(false);
}

const Widget* Widget::widget_parent() const
{
    return impl_->widget_parent();
}

void Widget::set_widget_parent(Widget* parent) const
{
    impl_->set_widget_parent(parent);
}

const std::vector<Widget*>& Widget::widget_children() const
{
    return impl_->widget_children_;
}

void Widget::set_enable(bool b) const { impl_->set_enable(b); }


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

bool Widget::is_showing() const {
    return *impl_->visible_sc_;
}

bool Widget::is_hiding() const {
    return !*impl_->visible_sc_;
}

bool Widget::enabled() const { return impl_->enabled(); }

bool Widget::visible() const {
    return impl_->visible();
}

int Widget::flags() const {
    return impl_->flags_;
}

WidgetType Widget::widget_type() const {
    return impl_->widget_type_;
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
