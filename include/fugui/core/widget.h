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

    static bool IsInUIThread();

    virtual void Show();
    virtual void Close();
    virtual void Hide();

    const Widget* widget_parent() const;
    void set_widget_parent(Widget* parent) const;
    const std::vector<Widget*>& widget_children() const;

    void set_enable(bool b) const;

    Vector2 size() const;
    void set_size(const Vector2& size) const;

    bool orphaned() const;
    bool is_showing() const;
    bool is_hiding() const;
    bool enabled() const;
    bool visible() const;
    int flags() const;
    WidgetType widget_type() const;

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    MW_SIGNALS_BEGIN(Widget)
    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)
    MW_SIGNALS_END()

protected:
    virtual void UpdateEarly();
    virtual void PaintBegin();
    virtual void PaintEnd();

    virtual void DoEnable(bool b) {}
    virtual void DoShow() {}
    virtual void DoHide() {}

private:
    using Object::parent;
    using Object::set_parent;

    friend class WidgetsDriver;
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
