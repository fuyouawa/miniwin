#pragma once
#include <fugui/tools/scope_variable.h>
#include <fugui/core/widget.h>

namespace fugui {
class Widget::Impl
{
public:
    ScopeCondition enable_sc_;
    ScopeCondition visible_sc_;
    ScopeVariable<Vector2> size_sc_;
    bool is_painting_children_;
    int flags_;
    WidgetType widget_type_;

    Widget* owner_;

    explicit Impl(Widget* owner);
    ~Impl();

    void PaintBegin();
    void PaintEnd();

    bool visible() const;
    void set_visible(bool b);
    bool enabled() const;
    void set_enable(bool b);
};
}
