#pragma once
#include <fugui/core/object.h>

#include <fugui/tools/container.h>

namespace fugui {
enum class WidgetType {
    kNone,
    kWindow,
    kControl,
    kMinimumControl
};

class Widget : public Object {
public:
    Widget(Widget* parent, std::u8string_view name, bool show, WidgetType widget_type);
    ~Widget() override;

    void Show();
    void Hide();

    const Widget* parent_widget() const;
    Widget* parent_widget();
    void set_parent(Widget* parent) const;

    void set_enable(bool b) const;

    Vector2 size() const;
    void set_size(const Vector2& size) const;

    bool is_showing() const;
    bool is_hiding() const;
    bool enabled() const;
    bool visible() const;
    int flags() const;
    WidgetType widget_type() const;

    MW_SIGNALS_BEGIN(Widget)
    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)
    MW_SIGNALS_END()

protected:
    virtual void PaintBegin() const;
    virtual void PaintEnd() const;
    virtual void DoEnable(bool b) {}
    virtual void DoShow() {}
    virtual void DoHide() {}

private:
    using Object::set_parent;

    friend class WidgetsDriver;
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
