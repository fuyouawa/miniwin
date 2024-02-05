#pragma once
#include <functional>
#include <memory>
#include <string_view>
#include <mvcgui/tools/scope_variable.h>
#include <mvcgui/core/object.h>
#include <mvcgui/core/signal.h>
#include <vector>

namespace mvcgui {
namespace internal {
class WidgetTreeNode;
class WidgetEngine;
using WidgetTreeNodePtr = std::shared_ptr<WidgetTreeNode>;
}

class Widget : public Object {
    friend class internal::WidgetTreeNode;
    friend class internal::WidgetEngine;
public:
    enum class Type {
        kWindow,
        kControl,
        kMinimumControl
    };

    Widget(Widget* const parent, bool show);
    virtual ~Widget();

    void Show();
    void Close();
    void Hide();
    void EnableFlags(bool b, int flags);

    void set_enable(bool b);
    void set_pause(bool b);

    virtual Widget* parent() const;
    virtual void set_parent(Widget* parent);

    //TODO sizeºÍposµÄapi
    auto size() const { return size_; }
    void set_size(const Vector2& size) { size_ = size; }

    bool is_showing() const;
    bool is_hiding() const;
    bool is_closed() const;
    bool enable() const;
    auto& id() const { return id_; }

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

    ScopeCondition enable_sc_;
    ScopeCondition visible_sc_;
    Vector2 size_;

    bool is_painting_children_;

    int flags_;
    bool pause_;
    bool initialized_;
    Type widget_type_;
    std::u8string id_;

private:
    internal::WidgetTreeNodePtr owning_node_;
    bool resume_visible_;
};
}