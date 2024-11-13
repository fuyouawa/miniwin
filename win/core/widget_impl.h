#pragma once
#include <miniwin/core/widget.h>

#include <queue>
#include <mutex>

#include <miniwin/tools/scope_variable.h>

namespace miniwin {
class Widget::Impl
{
public:
    explicit Impl(Widget* owner);
    ~Impl();

    void Close();
    void PaintBegin();
    void PaintEnd();

    Window* OwnerWindow();
 	Widget* WidgetParent();
    void SetWidgetParent(Widget* parent);

    void PushPendingFunctor(std::function<void()>&& func);
    void DoPendingFunctors();

    bool Visible() const;
    void SetVisible(bool b);
    bool Enabled() const;
    void SetEnable(bool b);

    ScopeCondition enable_sc_{ true };
    ScopeCondition visible_sc_{ true };
    ScopeVariable<Vector2D> size_sc_{};
    ScopeVariable<Vector2D> pos_sc_{};

    bool is_painting_children_ = false;
    bool orphaned_ = false;
    bool dirty_ = false;
    bool is_window_ = false;
    FlagsType draw_flags_ = 0;

    Widget* owner_;
    WidgetId id_;
    std::mutex pending_functors_mutex_;
    List<std::function<void()>> pending_functors_;
};
}
