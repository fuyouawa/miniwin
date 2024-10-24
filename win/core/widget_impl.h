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

    const Widget* WidgetParent() const;
    void SetWidgetParent(Widget* parent);

    //TODO 未来改成事件系统
    void OnChildrenChanged();

    void PushPendingFunctor(std::function<void()>&& func);
    void DoPendingFunctors();

    bool Visible() const;
    void SetVisible(bool b);
    bool Enabled() const;
    void SetEnable(bool b);

    ScopeCondition enable_sc_{ true };
    ScopeCondition visible_sc_{ true };
    ScopeVariable<Vector2> size_sc_{};

    bool is_painting_children_ = false;
    bool orphaned_ = false;
    bool dirty_ = false;

    FlagsType draw_flags_ = 0;

    Widget* owner_;
    String id_;
    std::mutex pending_functors_mutex_;
    std::queue<std::function<void()>> pending_functors_;
    std::vector<Widget*> widget_children_;
};
}
