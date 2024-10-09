#include <fugui/core/widget.h>
#include <imgui/imgui.h>
#include <fugui/tools/container.h>
#include <gui/tools/algorithm.h>
#include <gui/internal/widget_engine.h>
#include <gui/tools/scope_variable.h>
#include <gui/core/widget_p.h>

namespace fugui {
Widget::Widget(Widget* const parent, bool show, WidgetType widget_type)
{
    p_ = new internal::WidgetPrivate();
    p_->widget_type_ = widget_type;
    internal::WidgetEngine::instance().InitializeWidget(this, parent);
    if (!show) {
        Hide();
    }
}

Widget::~Widget() {
    assert(is_destroyed_);
    delete p_;
}

void Widget::Show() {
    assert(!is_closed());
    internal::WidgetEngine::instance().ModifyVisible(this, true);
}

void Widget::Close() {
    internal::WidgetEngine::instance().CloseWidget(this);
}

void Widget::Hide() {
    assert(!is_closed());
    internal::WidgetEngine::instance().ModifyVisible(this, false);
}

void Widget::set_enable(bool b) const { p_->enable_sc_.set_control(b); }

Widget* Widget::parent() const {
    return internal::WidgetEngine::instance().GetParent(this);
}

void Widget::set_parent(Widget* parent) {
    internal::WidgetEngine::instance().ModifyParent(this, parent);
}

Vector2 Widget::size() const {
    return p_->size_sc_.get();
}

void Widget::set_size(const Vector2& size) const {
    p_->size_sc_.set_control(size);
}

bool Widget::is_showing() const {
    return *p_->visible_sc_ && !is_destroyed_;
}

bool Widget::is_hiding() const {
    return !*p_->visible_sc_ && !is_destroyed_;
}

bool Widget::is_closed() const {
    return is_destroyed_;
}

bool Widget::enable() const { return *p_->enable_sc_; }

int Widget::flags() const {
    return p_->flags_;
}

WidgetType Widget::widget_type() const {
    return p_->widget_type_;
}

void Widget::Invoke(Functor&& func, InvokeType type) const {
    switch (type)
    {
    case InvokeType::kAuto:
        if (IsInOwnerThread()) {
            Invoke(std::move(func), InvokeType::kDirect);
        }
        else {
            Invoke(std::move(func), InvokeType::kQueued);
        }
        break;
    case InvokeType::kDirect:
        func();
        break;
    case InvokeType::kQueued:
        internal::WidgetEngine::instance().InvokeInNextFrame(std::move(func));
        break;
    default:
        assert(false);
        break;
    }
}

void Widget::Destroy() {
    OnDestroy();
    Object::Destroy();
}

void Widget::OnEnter()
{
    p_->enable_sc_.Entry();
    p_->visible_sc_.Entry();

    if (p_->enable_sc_.is_changed()) {
        if (*p_->enable_sc_) {
            Emit(on_enable_);
            OnEnable();
        }
        else {
            Emit(on_disable_);
            OnDisable();
        }
    }

    if (p_->visible_sc_.is_changed()) {
        if (*p_->visible_sc_) {
            Emit(on_show_);
            OnShow();
        }
        else {
            Emit(on_hide_);
            OnHide();
        }
    }
}

void Widget::OnPaintBegin()
{
    if (!*p_->enable_sc_) {
        ImGui::BeginDisabled();
    }
}

void Widget::OnUpdate() {
}

void Widget::OnPaintEnd()
{
    if (!*p_->enable_sc_) {
        ImGui::EndDisabled();
    }
}

void Widget::OnExit()
{
    p_->enable_sc_.Exit();
    p_->visible_sc_.Exit();
    p_->initialized_ = true;
}

void Widget::EnableFlags(bool b, int flags) const
{
    p_->flags_ = fugui::EnableFlags(p_->flags_, flags, b);
}
}