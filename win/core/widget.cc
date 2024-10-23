#include <format>
#include <miniwin/core/widget.h>
#include <miniwin/tools/container.h>
#include <miniwin/tools/scope_variable.h>

#include <win/core/widget_impl.h>
#include "win/tools/inner.h"

#include "widgets_driver.h"
#include "miniwin/widgets/window.h"

namespace miniwin {
WidgetDrawFlags operator|(WidgetDrawFlags a, WidgetDrawFlags b) { return Or(a, b); }
WidgetDrawFlags operator&(WidgetDrawFlags a, WidgetDrawFlags b) { return And(a, b); }

Widget::Widget(Widget* parent, std::u8string_view name, std::u8string_view id)
    : Object(parent, name)
{
    impl_ = std::make_unique<Impl>(this);
    impl_->id_ = id;
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

void Widget::SetWidgetParent(Widget* parent)
{
    impl_->SetWidgetParent(parent);
}

const std::vector<Widget*>& Widget::WidgetChildren() const
{
    return impl_->widget_children_;
}

std::optional<size_t> Widget::IndexOfWidgetChild(const Widget* child) const
{
    size_t i = 0;
	for (auto& c : WidgetChildren())
	{
		if (c == child)
		{
            return i;
		}
        i++;
	}
    return std::nullopt;
}

bool Widget::SetWidgetChildIndex(const Widget* child, size_t index)
{
    auto cs = const_cast<std::vector<Object*>&>(Children());
    auto index_it = cs.end();
    auto found_it = cs.end();
    for (size_t i = 0; i < cs.size(); ++i)
    {
        auto it = cs.begin() + i;
        if (i == index)
        {
            index_it = it;
        }
        if (*it == child)
        {
            found_it = it;
        }
    }
    if (index_it == cs.end() || found_it == cs.end())
        return false;
    if (index_it == found_it)
        return true;
    std::swap(*index_it, *found_it);
    return true;
}

void Widget::SetEnable(bool b) const { impl_->SetEnable(b); }


Vector2 Widget::Size() const {
    return impl_->size_sc_.get();
}

void Widget::SetSize(const Vector2& size) {
    impl_->size_sc_.SetControl(size);
}

std::u8string_view Widget::Id() const
{
    return impl_->id_;
}

void Widget::SetId(std::u8string_view id)
{
    impl_->id_ = id;
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

void Widget::OnBeforePaintChild(size_t child_index)
{
}

void Widget::OnAfterPaintChild(size_t child_index)
{
}
}
