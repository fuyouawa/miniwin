#pragma once
#include <fugui/tools/scope_variable.h>
#include <fugui/core/widget.h>
#include <queue>
#include <mutex>

namespace fugui {
class Widget::Impl
{
public:
    ScopeCondition enable_sc_;
    ScopeCondition visible_sc_;
    ScopeVariable<Vector2> size_sc_;
    bool is_painting_children_;
    int flags_;
    bool orphaned_;
    bool dirty_;
    WidgetType widget_type_;
    Widget* owner_;
    std::mutex pending_functors_mutex_;
    std::queue<std::function<void()>> pending_functors_;
    std::vector<Widget*> widget_children_;

    explicit Impl(Widget* owner);
    ~Impl();

    void Close();
    void PaintBegin();
    void PaintEnd();

    const Widget* widget_parent() const;
    void set_widget_parent(Widget* parent);

    //TODO 未来改成事件系统
    void OnChildrenChanged();

    void PushPendingFunctor(std::function<void()>&& func);
    void DoPendingFunctors();

    bool visible() const;
    void set_visible(bool b);
    bool enabled() const;
    void set_enable(bool b);
};
}
