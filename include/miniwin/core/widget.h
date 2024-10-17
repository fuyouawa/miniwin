#pragma once
#include <miniwin/core/object.h>
#include <miniwin/core/flags.h>

#include <miniwin/tools/container.h>
#include <miniwin/tools/property.h>

namespace miniwin {
enum class WidgetType {
    kNone,
    kWindow,
    kControl,
    kView
};

class Widget : public Object, public NonCopyable {
public:
    Widget(Widget* parent, std::u8string_view name, WidgetType widget_type);
    ~Widget() override;

    static bool IsInUIThread();

    virtual void Close();

    const Widget* WidgetParent() const;
    void SetWidgetParent(Widget* parent) const;
    const std::vector<Widget*>& WidgetChildren() const;

    virtual bool Visible() const;
    virtual void SetVisible(bool b) const;
    virtual bool Enabled() const;
    virtual void SetEnable(bool b) const;

    Vector2 size() const;
    void set_size(const Vector2& size) const;

    bool orphaned() const;
    WidgetType widget_type() const;
    WidgetDrawFlags draw_flags() const;
    void set_draw_flags(WidgetDrawFlags draw_flags);

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    virtual void UpdateEarly();
    virtual void PaintBegin();
    virtual void PaintEnd();

    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)

protected:
    virtual void DoEnable(bool b) {}
    virtual void DoShow() {}
    virtual void DoHide() {}

private:
    friend class WidgetsDriver;
    using Object::Parent;
    using Object::SetParent;

    _MW_IMPL
};
}
