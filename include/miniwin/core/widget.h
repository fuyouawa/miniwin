#pragma once
#include <miniwin/core/object.h>
#include <miniwin/tools/vector2d.h>
#include <miniwin/tools/variant.h>

namespace miniwin {
class WidgetsDriver;
class Window;
class Layout;

class Widget : public Object {
	MW_OBJECT
public:
	enum DrawFlags {
		kDrawIgnoreNone = 0,
		kDrawIgnoreChildren = 1 << 0,
		kDrawIgnoreSelf = 1 << 1,
		kDrawIgnoreDraw = kDrawIgnoreChildren | kDrawIgnoreSelf
	};

	Widget();
	~Widget() override;

	bool IsInUiThread() const;

	virtual void Show();
	virtual void Hide();
	virtual void Close();

	bool IsWindow() const;

	SharedWindow OwnerWindow() const;
	SharedWidget WidgetParent() const;

	void SetWidgetParent(const SharedWidget& parent);
	List<SharedWidget> WidgetChildren() const;

	virtual bool Visible() const;
	virtual void SetVisible(bool b);
	virtual bool Enabled() const;
	virtual void SetEnable(bool b);
	bool IsStarted() const;
	bool IsUpdated() const;

	WidgetId Id() const;

	virtual Vector2D Position() const = 0;
	virtual void SetPosition(const Vector2D& pos) = 0;
	virtual Vector2D Size() const = 0;
	virtual void SetSize(const Vector2D& size) = 0;

	void SetSize(float width, float height);
	void SetWidth(float width);
	void SetHeight(float height);

	float Alpha() const;
	float BgAlpha() const;
	void SetAlpha(float alpha);
	void SetBgAlpha(float alpha);

	FlagsType GetDrawFlags() const;
	void SetDrawFlags(FlagsType flags);

	void Invoke(std::function<void()> func, InvokeType invoke_type = InvokeType::kAuto) const override;

	void Initialize(const SharedObject& parent) override;

	MW_SIGNAL(OnClosed)
	MW_SIGNAL(OnEnableChanged, (bool)b)
	MW_SIGNAL(OnVisbleChanged, (bool)b)
	MW_SIGNAL(OnSizeChanged, (const Vector2D&)size, (const Vector2D&)prev_size)
	MW_SIGNAL(OnPositionChanged, (const Vector2D&)position, (const Vector2D&)prev_position)

protected:
	virtual void Awake();
	virtual void Start();

	// 是所有绘制之前的准备工作
	// 会先调用完所有Widget的PreparePaint后才会进入PaintBegin
	virtual void PreparePaint();
	// 开始绘制
	// 会先调用父类的PaintBegin, 然后会递归调用所有子类的PaintBegin
	// 相当于二叉树遍历中的左叶子
	virtual void PaintBegin(size_t index);
	// 结束绘制
	// 和PaintBegin相对应
	// 相当于二叉树遍历中的右叶子
	virtual void PaintEnd(size_t index);

private:
	friend class WidgetsDriver;
	friend class Window;
	friend class Layout;

	using Object::Parent;
	using Object::SetParent;

	_MW_IMPL
};
}
