#pragma once
#include <optional>

#include <miniwin/core/object.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/property.h>
#include <miniwin/tools/variant.h>

namespace miniwin {
class Window;

class Widget : public Object, public NonCopyMoveable {
public:
    enum GetDrawFlags
    {
        kDrawIgnoreNone = 0,
        kDrawIgnoreChildren = 1 << 0,
        kDrawIgnoreSelf = 1 << 1,
        kDrawIgnoreDraw = kDrawIgnoreChildren | kDrawIgnoreSelf
    };

    Widget(Widget* parent, const String& name, const String& id = "Widget");
    ~Widget() override;

    static bool IsInUIThread();

    virtual void Show();
    virtual void Hide();
    virtual void Close();

    bool IsWindow() const;
    const Window* OwnerWindow() const;
    const Widget* WidgetParent() const;
    Window* OwnerWindow();
    Widget* WidgetParent();

    void SetWidgetParent(Widget* parent);
    List<Widget*> WidgetChildren() const;

    virtual bool Visible() const;
    virtual void SetVisible(bool b);
    virtual bool Enabled() const;
    virtual void SetEnable(bool b);

    const String& Id() const;
    void SetId(const String& id);

    virtual Vector2D Size() const;
    virtual void SetSize(const Vector2D& size);
    virtual Vector2D Position() const;
    virtual void SetPosition(const Vector2D& pos);

    bool Orphaned() const;
    FlagsType GetDrawFlags() const;
    void SetDrawFlags(FlagsType flags);

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)
    MW_SIGNAL(OnSizeChanged, (const Vector2D&) size, (const Vector2D&) prev_size)
    MW_SIGNAL(OnPositionChanged, (const Vector2D&) position, (const Vector2D&) prev_position)

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

private:
    friend class WidgetsDriver;
    friend class Window;
    using Object::Parent;
    using Object::SetParent;

    _MW_IMPL
};
}
