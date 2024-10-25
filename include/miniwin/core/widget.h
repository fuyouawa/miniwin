#pragma once
#include <optional>

#include <miniwin/core/object.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/property.h>
#include <miniwin/tools/variant.h>

namespace miniwin {
class Widget : public Object, public NonCopyMoveable {
public:
    enum DrawFlags
    {
        kDrawIgnoreNone = 0,
        kDrawIgnoreChildren = 1 << 0,
        kDrawIgnoreSelf = 1 << 1,
        kDrawIgnoreDraw = kDrawIgnoreChildren | kDrawIgnoreSelf
    };

    Widget(Widget* parent, const String& name, const String& id = u8"Widget");
    ~Widget() override;

    static bool IsInUIThread();

    virtual void Close();

    const Widget* WidgetParent() const;
    void SetWidgetParent(Widget* parent);
    const List<Widget*>& WidgetChildren() const;

    size_t IndexOfWidgetChild(const Widget* child) const;
    bool SetWidgetChildIndex(const Widget* child, size_t index);

    virtual bool Visible() const;
    virtual void SetVisible(bool b) const;
    virtual bool Enabled() const;
    virtual void SetEnable(bool b) const;

    const String& Id() const;
    void SetId(const String& id);

    virtual Vector2D Size() const;
    virtual void SetSize(const Vector2D& size);

    bool Orphaned() const;
    FlagsType DrawFlags() const;
    void SetDrawFlags(FlagsType flags);

    void Invoke(std::function<void()>&& func, InvokeType invoke_type = InvokeType::kAuto) const override;

    MW_SIGNAL(OnEnableChanged, (bool) b)
    MW_SIGNAL(OnVisbleChanged, (bool) b)
    MW_SIGNAL(OnSizeChanged, (Vector2D) size, (Vector2D) prev_size)

protected:
    // �����л���֮ǰ��׼������
    // ���ȵ���������Widget��PreparePaint��Ż����PaintBegin
    virtual void PreparePaint();
    // ��ʼ����
    // ���ȵ��ø����PaintBegin, Ȼ���ݹ�������������PaintBegin
    // �൱�ڶ����������е���Ҷ��
    virtual void PaintBegin();
    // ��������
    // ��PaintBegin���Ӧ
    // �൱�ڶ����������е���Ҷ��
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
