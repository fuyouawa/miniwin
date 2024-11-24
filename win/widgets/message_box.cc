#include <miniwin/widgets/message_box.h>

#include <miniwin/widgets/layout/box_layout.h>
#include <miniwin/widgets/label.h>

#include "win/tools/debug.h"

namespace miniwin {
class MessageBox::Impl {
public:
	Impl(MessageBox* owner) : owner_(owner) {}

	void Awake() {
		lab_msg_ = Create<Label>(owner_->shared_from_this());
		layout_btns_ = Create<HBoxLayout>(owner_->shared_from_this());
		layout_btns_->SetSpacing(10);
		layout_btns_->SetAlignment(1);
		owner_->SetSize({ 200, 110 });
	}

	void AddButton(const std::shared_ptr<Button>& btn) {
		btn->SetWidgetParent(owner_->shared_from_this());
		btns_.PushBack(btn);
		layout_btns_->AddWidget(btn);
		Connect(btn, &Button::OnClicked, owner_->shared_from_this(), [btn, cb = &callback_]() {
			(*cb)(btn);
		});
	}

	MessageBox* owner_ = nullptr;
	std::shared_ptr<HBoxLayout> layout_btns_;
	std::shared_ptr<Label> lab_msg_ = nullptr;
	List<std::shared_ptr<Button>> btns_;
	Callback callback_;
};

void MessageBox::InformationAsync(const SharedWidget& parent, const String& title, const String& text, const String& ok,
                                  std::function<void()> callback) {
	auto msg = Create<MessageBox>(parent);
	msg->SetTitle(title);
	msg->SetText(text);

	auto btn = Create<Button>(msg);
	btn->SetText(ok);
	msg->AddButton(btn);

	msg->SetButtonClickedCallback([cb = callback, msg](auto& btn) {
		cb();
		msg->Close();
	});

	Connect(msg, &MessageBox::OnVisbleChanged, msg, [cb = std::move(callback)](bool visible) {
		if (!visible) {
			cb();
		}
	});

	msg->Open();
}

void MessageBox::QuestionAsync(const SharedWidget& parent, const String& title, const String& text, const String& yes,
                               const String& no, std::function<void(bool is_yes)> callback) {
	auto msg = Create<MessageBox>(parent);
	msg->SetTitle(title);
	msg->SetText(text);

	auto yes_btn = Create<Button>(msg);
	yes_btn->SetText(yes);
	auto no_btn = Create<Button>(msg);
	no_btn->SetText(no);

	msg->AddButton(yes_btn);
	msg->AddButton(no_btn);

	msg->SetButtonClickedCallback([cb = callback, msg, yes_btn, no_btn](auto& btn) {
		cb(btn == yes_btn);
		if (btn != yes_btn)
			MW_ASSERT_X(btn == no_btn);
		msg->Close();
	});

	Connect(msg, &MessageBox::OnVisbleChanged, msg, [cb = std::move(callback)](bool visible) {
		if (!visible) {
			cb(false);
		}
	});

	msg->Open();
}

MessageBox::MessageBox() {
	impl_ = std::make_unique<Impl>(this);
}

MessageBox::~MessageBox() {}

void MessageBox::AddButton(const std::shared_ptr<Button>& btn) {
	impl_->AddButton(btn);
}

void MessageBox::SetButtonClickedCallback(std::function<void(const std::shared_ptr<Button>& btn)> callback) {
	impl_->callback_ = std::move(callback);
}

String MessageBox::Text() const {
	return impl_->lab_msg_->Text();
}

void MessageBox::SetText(const String& text) {
	impl_->lab_msg_->SetText(text);
}

void MessageBox::Awake() {
	Dialog::Awake();
	impl_->Awake();
}
}
