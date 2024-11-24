#include "platform_easy_window_impl.h"

namespace miniwin {
PlatformEasyWindowImpl::PlatformEasyWindowImpl(const String& title, const Vector2DInt& size, bool client_size,
                                               FlagsType styles, const SharedPlatformEasyWindow& parent) {
	auto p = dynamic_cast<PlatformEasyWindowImpl*>(parent.get());
	win_ = EasyWindow::Create(title, size, client_size, styles, p ? p->win_ : nullptr);

	win_->on_close_ = [this]() {
		if (on_close_)
			return on_close_();
		return true;
	};
	win_->on_forced_ = [this](bool forced) {
		if (on_forced_)
			on_forced_(forced);
	};
	win_->on_moved_ = [this](Vector2DInt pos) {
		if (on_moved_)
			on_moved_(std::move(pos));
	};
	win_->on_resized_ = [this](Vector2DInt size) {
		OnResized(size);
		if (on_resized_)
			on_resized_(std::move(size));
	};
}

void PlatformEasyWindowImpl::Repaint() {
	win_->Repaint();
}

void PlatformEasyWindowImpl::Show(bool show_or_hide) {
	win_->Show(show_or_hide);
}

bool PlatformEasyWindowImpl::IsFocused() const {
	return win_->IsFocused();
}

void PlatformEasyWindowImpl::SetFocus() {
	win_->SetFocus();
}

void PlatformEasyWindowImpl::SetSize(const Vector2DInt& size, bool adjust) {
	win_->SetSize(size, adjust);
}

void PlatformEasyWindowImpl::SetPosition(const Vector2DInt& pos, bool adjust) {
	win_->SetPosition(pos, adjust);
}

void PlatformEasyWindowImpl::SetMaximized(bool b) {
	win_->SetMaximized(b);
}

void PlatformEasyWindowImpl::SetMinimized(bool b) {
	win_->SetMinimized(b);
}

void PlatformEasyWindowImpl::SetTitle(const String& title) {
	win_->SetTitle(title);
}

void PlatformEasyWindowImpl::SetAlpha(uint8_t alpha) {
	win_->SetAlpha(alpha);
}

void PlatformEasyWindowImpl::SetCursor(EasyWindow::CursorType cursor) {
	win_->SetCursor(cursor);
}

Vector2DInt PlatformEasyWindowImpl::Size() const {
	return win_->Size();
}

Vector2DInt PlatformEasyWindowImpl::Position() const {
	return win_->Position();
}

bool PlatformEasyWindowImpl::IsMaximized() const {
	return win_->IsMaximized();
}

bool PlatformEasyWindowImpl::IsMinimized() const {
	return win_->IsMinimized();
}

bool PlatformEasyWindowImpl::Update() {
	return win_->Update();
}

void* PlatformEasyWindowImpl::PlatformHandle() const {
	return win_->PlatformHandle();
}
}
