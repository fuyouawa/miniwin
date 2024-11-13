#include <miniwin/widgets/message_box.h>

#include <miniwin/widgets/layout/box_layout.h>
#include <miniwin/widgets/label.h>

#include "win/tools/debug.h"

namespace miniwin {
class MessageBox::Impl {
public:
	Impl(MessageBox* owner) : owner_(owner) {}

	void Init(const String& text) {
		lab_msg_ = new Label(owner_, text);
		layout_btns_ = new HBoxLayout(owner_);
		layout_btns_->SetSpacing(10);
		owner_->SetSize({ 200, 110 });
	}

	void AddButton(Button* btn) {
		btn->SetWidgetParent(owner_);
		btns_.PushBack(btn);
		layout_btns_->AddWidget(btn);
		Connect(btn, &Button::OnClicked, owner_, [btn, cb = &callback_]() {
			(*cb)(btn);
		});
	}

	MessageBox* owner_ = nullptr;
	HBoxLayout* layout_btns_ = nullptr;
	Label* lab_msg_ = nullptr;
	List<Button*> btns_;
	std::function<void(Button* btn)> callback_;
};

void MessageBox::InformationAsync(Widget* parent, const String& title, const String& text, const String& ok,
	std::function<void()> clicked_callback)
{
	auto msg = new MessageBox(parent, title, text);
	msg->EnableCloseButton(false);
	msg->AddButton(new Button(msg, ok));
	msg->SetButtonClickedCallback([cb = std::move(clicked_callback), msg](Button* btn) {
		cb();
		msg->Close();
		});

	msg->Open();
}

void MessageBox::QuestionAsync(Widget* parent, const String& title, const String& text, const String& yes,
	const String& no, std::function<void(bool yes)> clicked_callback)
{
	auto msg = new MessageBox(parent, title, text);
	msg->EnableCloseButton(false);
	auto yes_btn = new Button(msg, yes);
	auto no_btn = new Button(msg, no);

	msg->AddButton(yes_btn);
	msg->AddButton(no_btn);

	msg->SetButtonClickedCallback([cb = clicked_callback, msg, yes_btn, no_btn](Button* btn) {
		cb(btn == yes_btn);
		if (btn != yes_btn)
			MW_ASSERT_X(btn == no_btn);
		msg->Close();
		});

	Connect(msg, &MessageBox::OnClosed, msg, [cb = std::move(clicked_callback)]() {
		cb(false);
		});

	msg->Open();
}

MessageBox::MessageBox(Widget* parent, const String& title, const String& text)
	: Dialog(parent, title) {
	impl_ = std::make_unique<Impl>(this);
	impl_->Init(text);
}

void MessageBox::AddButton(Button* btn) {
	impl_->AddButton(btn);
}

void MessageBox::SetButtonClickedCallback(std::function<void(Button* btn)> callback) {
	impl_->callback_ = std::move(callback);
}
}
