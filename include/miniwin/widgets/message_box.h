#pragma once
#include <miniwin/widgets/dialog.h>
#include <miniwin/widgets/button.h>

namespace miniwin {
class MessageBox : public Dialog {
	MW_OBJECT
public:
	using Callback = std::function<void(const std::shared_ptr<Button>& btn)>;

	static void InformationAsync(
		const SharedWidget& parent,
		const String& title,
		const String& text,
		const String& ok,
		std::function<void()> callback);
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
