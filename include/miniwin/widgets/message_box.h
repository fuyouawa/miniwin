#pragma once
#include <miniwin/widgets/dialog.h>
#include <miniwin/widgets/button.h>

namespace miniwin {
class MessageBox : public Dialog {
	MW_OBJECT
public:
	using Callback = std::function<void(const std::shared_ptr<Button>& btn)>;

	/**
	 * 弹出一个模态信息框
	 * @param parent 父级
	 * @param title 标题
	 * @param text 显示文本
	 * @param ok ok按钮的文本
	 * @param callback 按选中按钮的回调
	 */
	static void InformationAsync(
		const SharedWidget& parent,
		const String& title,
		const String& text,
		const String& ok,
		std::function<void()> callback);
	/**
	 * 弹出一个模态询问框
	 * @param parent 父级
	 * @param title 标题
	 * @param text 显示文本
	 * @param yes yes按钮的文本
	 * @param no no按钮的文本
	 * @param callback 按选中按钮的回调，如果点击的是yes，则参数的is_yes为true；反之如果点击的是no或者直接关闭窗体，则is_yes为false
	 */
	static void QuestionAsync(
		const SharedWidget& parent,
		const String& title,
		const String& text,
		const String& yes,
		const String& no,
		std::function<void(bool is_yes)> callback);

	MessageBox();
	~MessageBox() override;

	void AddButton(const std::shared_ptr<Button>& btn);
	void SetButtonClickedCallback(Callback callback);

	String Text() const;
	void SetText(const String& text);

protected:
	void Awake() override;

	_MW_IMPL
};
}
