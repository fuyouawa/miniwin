#pragma once
#include <miniwin/core/object.h>

#include <miniwin/tools/container.h>
#include <miniwin/tools/property.h>
#include <optional>

#include <miniwin/tools/variant.h>

namespace miniwin {
enum class WidgetDrawFlags
{
    kNone = 0,
    kIgnoreChildrenDraw = 1 << 0,
    kIgnoreSelfDraw = 1 << 1,
    kIgnoreDraw = kIgnoreChildrenDraw | kIgnoreSelfDraw
};

WidgetDrawFlags operator|(WidgetDrawFlags a, WidgetDrawFlags b);
WidgetDrawFlags operator&(WidgetDrawFlags a, WidgetDrawFlags b);

class Widget : public Object, public NonCopyMoveable {
public:
    Widget(Widget* parent, std::u8string_view name, std::u8string_view id = u8"Widget");
    ~Widget() override;

    static bool IsInUIThread();

    virtual void Close();

    const Widget* WidgetParent() const;
    void SetWidgetParent(Widget* parent);
    const std::vector<Widget*>& WidgetChildren() const;

    std::optional<size_t> IndexOfWidgetChild(const Widget* child) const;
    bool SetWidgetChildIndex(const Widget* child, size_t index);

    virtual bool Visible() const;
    virtual void SetVisible(bool b) const;
    virtual bool Enabled() const;
    virtual void SetEnable(bool b) const;

    std::u8string_view Id() const;
    void SetId(std::u8string_view id);

    virtual Vector2 Size() const;
    virtual void SetSize(const Vector2& size);

    bool Orphaned() const;
    WidgetDrawFlags DrawFlags() const;
    void SetDrawFlags(WidgetDrawFlags draw_flags);

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)
    MW_SIGNAL(OnSizeChanged, (Vector2) size, (Vector2) prev_size)

protected:
    // 是所有绘制之前的准备工作
    // 会先调用完所有Widget的PreparePaint后才会进入PaintBegin
    virtual void PreparePaint();
    // 开始绘制
    // 会先调用父类的PaintBegin, 然后会递归调用所有子类的PaintBegin
    // 相当于二叉树遍历中的左叶子
    virtual void PaintBegin();
    // 结束绘制
    // 和PaintBegin相对应
    // 相当于二叉树遍历中的右叶子
    virtual void PaintEnd();

    virtual void OnBeforePaintChild(size_t child_index);
    virtual void OnAfterPaintChild(size_t child_index);

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
