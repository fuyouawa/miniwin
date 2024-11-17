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

    void Awake();

    SharedWindow OwnerWindow() const;
	SharedWidget WidgetParent() const;
    void SetWidgetParent(const SharedWidget& parent);

    void PushPendingFunctor(std::function<void()>&& func);
    void DoPendingFunctors();

    bool Visible() const;
    void SetVisible(bool b);
    bool Enabled() const;
    void SetEnable(bool b);

    ScopeCondition enable_sc_{ true };
    ScopeVariable<Vector2D> size_sc_{};
    ScopeVariable<Vector2D> pos_sc_{};

    bool visible_ = true;
    bool awaked_ = false;
    bool is_painting_children_ = false;
    bool is_window_ = false;
    FlagsType draw_flags_ = 0;

    Widget* owner_;
    Layout* layout_ = nullptr;
    WidgetId id_ = 0;
    std::mutex pending_functors_mutex_;
    List<std::function<void()>> pending_functors_;
};
}
