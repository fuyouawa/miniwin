#include <format>
#include <fugui/core/widget.h>
#include <fugui/tools/container.h>
#include <fugui/tools/scope_variable.h>

#include <gui/core/widget_impl.h>
#include <gui/internal/widget_engine.h>

namespace fugui {
Widget::Widget(Widget* parent, std::u8string_view name, bool show, WidgetType widget_type)
    : Object(parent, name)
{
    impl_ = std::make_unique<Impl>(this);
    impl_->widget_type_ = widget_type;
    if (!show) {
        Hide();
    }
}

Widget::~Widget()
{
}

void Widget::Show() {
    impl_->set_visible(true);
}

void Widget::Hide() {
    impl_->set_visible(false);
}

const Widget* Widget::parent_widget() const
{
    auto w = dynamic_cast<const Widget*>(parent());
    assert(w);
    return w;
}

Widget* Widget::parent_widget()
{
    auto w = dynamic_cast<Widget*>(parent());
    assert(w);
    return w;
}

void Widget::set_parent(Widget* parent) const
{
    Object::set_parent(parent);
}

void Widget::set_enable(bool b) const { impl_->set_enable(b); }


Vector2 Widget::size() const {
    return impl_->size_sc_.get();
}

void Widget::set_size(const Vector2& size) const {
    impl_->size_sc_.set_control(size);
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

void Widget::PaintBegin() const
{
    impl_->PaintBegin();
}

void Widget::PaintEnd() const
{
    impl_->PaintEnd();
}
}
