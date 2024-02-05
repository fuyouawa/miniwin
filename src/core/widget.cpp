#include <mvcgui/core/widget.h>
#include <imgui/imgui.h>
#include <mvcgui/core/application.h>
#include <mvcgui/tools/container.h>
#include <mvcgui/internal/framework/widget_engine.h>

namespace mvcgui {
Widget::Widget(Widget* const parent, bool show)
    : Object{},
    enable_sc_{ true },
    pause_{ false },
    is_painting_children_{ false },
    size_{},
	flags_{ false },
    owning_node_{ nullptr },
    widget_type_{ Type::kWindow },
    visible_sc_{ true },
    resume_visible_{ show },
    initialized_{ false }
{
    internal::WidgetEngine::instance().InitializeWidget(this, parent);
    if (!show) {
        Hide();
    }
}

Widget::~Widget() {
    assert(is_destroyed_);
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

void Widget::set_enable(bool b) { enable_sc_.set_control(b); }
void Widget::set_pause(bool b) { pause_ = b; }

Widget* Widget::parent() const {
    return internal::WidgetEngine::instance().GetParent(this);
}

void Widget::set_parent(Widget* parent) {
    internal::WidgetEngine::instance().ModifyParent(this, parent);
}

bool Widget::is_showing() const {
    return *visible_sc_ && !is_destroyed_;
}

bool Widget::is_hiding() const {
    return !*visible_sc_ && !is_destroyed_;
}

bool Widget::is_closed() const {
    return is_destroyed_;
}

bool Widget::enable() const { return *enable_sc_; }

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
    enable_sc_.Entry();
    visible_sc_.Entry();

    if (enable_sc_.is_changed()) {
        if (*enable_sc_) {
            Emit(on_enable_);
            OnEnable();
        }
        else {
            Emit(on_disable_);
            OnDisable();
        }
    }

    if (visible_sc_.is_changed()) {
        if (*visible_sc_) {
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
    if (!*enable_sc_) {
        ImGui::BeginDisabled();
    }
}

void Widget::OnUpdate() {
}

void Widget::OnPaintEnd()
{
    if (!*enable_sc_) {
        ImGui::EndDisabled();
    }
}

void Widget::OnExit()
{
    enable_sc_.Exit();
    visible_sc_.Exit();
    initialized_ = true;
}

void Widget::EnableFlags(bool b, int flags)
{
    if (b) {
        flags_ |= flags;
    }
    else {
        flags_ &= (~flags);
    }
}
}