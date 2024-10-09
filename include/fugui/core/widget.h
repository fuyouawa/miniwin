#pragma once
#include <fugui/core/object.h>
#include <fugui/core/signal.h>

namespace fugui {
namespace internal {
class WidgetTreeNode;
class WidgetEngine;

class WidgetPrivate;
}

enum class WidgetType {
    kNone,
    kWindow,
    kControl,
    kMinimumControl
};

class Widget : public Object {
    friend class internal::WidgetTreeNode;
    friend class internal::WidgetEngine;
public:

    Widget(Widget* const parent, bool show, WidgetType widget_type);
    ~Widget() override;

    void Show();
    void Close();
    void Hide();
    void EnableFlags(bool b, int flags) const;

    void set_enable(bool b) const;

    virtual Widget* parent() const;
    virtual void set_parent(Widget* parent);

    Vector2 size() const;
    void set_size(const Vector2& size) const;

    bool is_showing() const;
    bool is_hiding() const;
    bool is_closed() const;
    bool enable() const;
    int flags() const;
    WidgetType widget_type() const;

    void Invoke(Functor&& func, InvokeType type = InvokeType::kAuto) const override;

    Signal<> on_enable_;
    Signal<> on_disable_;
    Signal<> on_show_;
    Signal<> on_hide_;

protected:
    void Destroy() override;

    virtual void OnEnter();
    virtual void OnPaintBegin();
    virtual void OnUpdate();
    virtual void OnPaintEnd();
    virtual void OnExit();

    virtual void OnShow() {}
    virtual void OnDestroy() {}
    virtual void OnEnable() {}
    virtual void OnDisable() {}
    virtual void OnHide() {}

private:
    internal::WidgetPrivate* p_;
};
}