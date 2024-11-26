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

	bool IsWidget() const override;
	virtual bool IsWindow() const;
	virtual bool IsControl() const;

	SharedWindow OwnerWindow() const;
	SharedWidget WidgetParent() const;

	virtual void SetWidgetParent(const SharedWidget& parent);
	List<SharedWidget> WidgetChildren() const;

	virtual bool Visible() const;
	virtual void SetVisible(bool b);
	virtual bool Enabled() const;
	virtual void SetEnable(bool b);
	bool IsStarted() const;
	bool IsUpdated() const;

	WidgetId Id() const;

	virtual Vector2D Size() const = 0;
	virtual void SetSize(const Vector2D& size) = 0;

	void SetWidth(float width);
	void SetHeight(float height);

	float Alpha() const;
	float BgAlpha() const;
	void SetAlpha(float alpha);
	void SetBgAlpha(float alpha);

	FlagsType GetDrawFlags() const;
	void SetDrawFlags(FlagsType flags);

	bool Invoke(std::function<void()> func, InvokeType invoke_type = InvokeType::kAuto) const override;

	void Initialize(const SharedObject& parent) override;

	MW_SIGNAL(OnClosed)
	MW_SIGNAL(OnEnableChanged, (bool)b)
	MW_SIGNAL(OnVisbleChanged, (bool)b)
	MW_SIGNAL(OnSizeChanged, (const Vector2D&)size, (const Vector2D&)prev_size)
	MW_SIGNAL(OnPositionChanged, (const Vector2D&)position, (const Vector2D&)prev_position)

protected:
	virtual void Awake();
	virtual void Start();

	// 是所有更新之前的准备工作
	// 会先调用完所有Widget的PrepareUpdate后才会进入BeginUpdate
	virtual void PrepareUpdate();
	// 开始新一帧的更新
	// 会先调用父类的BeginUpdate, 然后会递归调用所有子类的BeginUpdate
	// 相当于二叉树遍历中的左叶子
	virtual void BeginUpdate(size_t index);
	// 结束当前帧的更新
	// 和BeginUpdate相对应
	// 相当于二叉树遍历中的右叶子
	virtual void EndUpdate(size_t index);

private:
	friend class WidgetsDriver;
	friend class Layout;

	using Object::Parent;
	void SetParent(const SharedObject& parent) const override;

	_MW_IMPL
};
}
