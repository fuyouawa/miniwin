#pragma once
#include <miniwin/widgets/dialog.h>
#include <miniwin/widgets/button.h>

namespace miniwin {
class MessageBox : public Dialog {
public:
	static void InformationAsync(
		Widget* parent,
		const String& title,
		const String& text,
		const String& ok,
		std::function<void()> callback);
	static void QuestionAsync(
		Widget* parent,
		const String& title,
		const String& text,
		const String& yes,
		const String& no,
		std::function<void(bool yes)> callback);

	MessageBox(Widget* parent, const String& title, const String& text);

	void AddButton(Button* btn);
	void SetButtonClickedCallback(std::function<void(Button* btn)> callback);

	_MW_IMPL
};
}