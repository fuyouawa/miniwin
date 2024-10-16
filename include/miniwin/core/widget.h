#pragma once
#include <miniwin/core/object.h>

#include <miniwin/tools/container.h>

namespace miniwin {
enum class WidgetType {
    kNone,
    kWindow,
    kControl,
    kView
};

enum class WidgetFlags
{
    kNone = 0,
    kIgnoreChildrenDraw = 1 << 0,
    kIgnoreDraw = 1 << 1,
};

WidgetFlags operator|(WidgetFlags x, WidgetFlags y);
WidgetFlags operator&(WidgetFlags x, WidgetFlags y);

class Widget : public Object {
public:
    Widget(Widget* parent, std::u8string_view name, WidgetType widget_type);
    ~Widget() override;

    static bool IsInUIThread();

    virtual void Close();

    const Widget* GetWidgetParent() const;
    void SetWidgetParent(Widget* parent) const;
    const std::vector<Widget*>& GetWidgetChildren() const;

    virtual bool GetVisible() const;
    virtual void SetVisible(bool b) const;
    virtual bool GetEnabled() const;
    virtual void SetEnable(bool b) const;

    Vector2 size() const;
    void set_size(const Vector2& size) const;

    bool orphaned() const;
    WidgetType widget_type() const;
    WidgetFlags widget_flags() const;
    void set_widget_flags(WidgetFlags widget_flags);

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)

protected:
    virtual void UpdateEarly();
    virtual void PaintBegin();
    virtual void PaintEnd();

    virtual void DoEnable(bool b) {}
    virtual void DoShow() {}
    virtual void DoHide() {}

private:
    using Object::GetParent;
    using Object::SetParent;

    friend class WidgetsDriver;

    _MW_IMPL
};
}
