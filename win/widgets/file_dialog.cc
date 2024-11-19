#include <miniwin/widgets/file_dialog.h>

#include <Windows.h>

#include <thread>
#include <mutex>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/regex.h>
#include <miniwin/tools/stringlist.h>

namespace miniwin {
namespace {
String OpenFileDialog(const SharedWidget& parent, const String& title, const String& dir, const String& filter,
                      String* selected_filter) {
	String windows_filter;

	auto filters = filter.Split(";;");
	for (auto& f : filters) {
		Regex r(R"((.+)\s*\((.+)\))");
		auto m = r.Match(f);
		if (m.HasMatch()) {
			auto desc = m.Captured(1);
			auto ext = m.Captured(2);

			windows_filter += desc + '\0' + ext.Replace(" ", ";") + '\0';
		}
	}

	OPENFILENAMEW ofn;

	wchar_t file[MAX_PATH]{0};
	ZeroMemory(&ofn, sizeof(ofn));
	if (parent) {
		auto w = parent->OwnerWindow();
		if (w)
			ofn.hwndOwner = reinterpret_cast<HWND>(w->PlatformHandle());
	}
	auto wfilter = windows_filter.ToStdWString();
	auto wtitle = title.ToStdWString();
	auto wdir = dir.ToStdWString();
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = file;
	ofn.nMaxFile = sizeof(file);
	ofn.lpstrFilter = wfilter.data();
	ofn.lpstrTitle = wtitle.data();
	ofn.lpstrInitialDir = wdir.data();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameW(&ofn)) {
		*selected_filter = filters[ofn.nFilterIndex == 0 ? 0 : ofn.nFilterIndex - 1];
		return String::FromUtf16(ofn.lpstrFile);
	}
	return {};
}
}

class FileDialog::Impl {
public:
	Impl(FileDialog* owner) : owner_(owner) {}

	void Awake() {
		owner_->EnableFlags(imgui::kWindowNoInputs
		                  | imgui::kWindowNoBackground
		                  | imgui::kWindowNoTitleBar, true);
		owner_->SetSize(Vector2D::kZero);
		owner_->SetPosition(Vector2D::kZero);
	}

	void DoOpenFileDialog() {
		if (!open_file_dialog_thread_.joinable()) {
			open_file_dialog_thread_ = std::thread([cfg = cfg_,cap = owner_->Title(), self = owner_->shared_from_this()]() {
				String sf;
				auto f = OpenFileDialog(
					cfg.parent.lock(),
					cap,
					cfg.directory,
					cfg.filter,
					&sf);

				{
					std::lock_guard lk(self->impl_->mutex_);
					self->impl_->file_ = std::move(f);
					self->impl_->selected_filter = std::move(sf);
				}
				self->impl_->selected_ = true;
				cfg.selected_callback(self);
			});
		}
	}

	FileDialog* owner_;
	std::thread open_file_dialog_thread_;
	std::atomic_bool selected_;
	String selected_filter;
	String file_;
	std::mutex mutex_;
	Config cfg_ = {};
};

void FileDialog::GetOpenFileNameAsync(const SharedWidget& parent, const String& title, CallbackOfGetOpenFileName callback,
                                      const String& dir, const String& filter) {
	auto dlg = Instantiate<FileDialog>(parent);
	dlg->SetTitle(title);
	dlg->GetConfig() = Config(parent, dir, filter, [cb = std::move(callback)](const std::shared_ptr<FileDialog>& dlg) {
		cb(std::move(dlg->impl_->file_), std::move(dlg->impl_->selected_filter));
		dlg->Close();
		});

	dlg->Open();
}

FileDialog::FileDialog()
{
	impl_ = std::make_unique<Impl>(this);
}

FileDialog::~FileDialog() {
	impl_->open_file_dialog_thread_.join();
}

FileDialog::Config& FileDialog::GetConfig() const {
	return impl_->cfg_;
}

bool FileDialog::IsSelectionCompleted() const {
	return impl_->selected_;
}

String FileDialog::SelectedFilter() const {
	// 如果选择完了，直接返回，否则需要加锁
	if (impl_->selected_) {
		return impl_->selected_filter;
	}

	std::lock_guard lk(impl_->mutex_);
	return impl_->selected_filter;
}

String FileDialog::SelectedFileName() const {
	// 如果选择完了，直接返回，否则需要加锁
	if (impl_->selected_) {
		return impl_->file_;
	}

	std::lock_guard lk(impl_->mutex_);
	return impl_->file_;
}

void FileDialog::Awake() {
	Dialog::Awake();
	impl_->Awake();
}

void FileDialog::OnPaintWindowBegin() {
	Dialog::OnPaintWindowBegin();

	impl_->DoOpenFileDialog();

	if (impl_->selected_) {
		Hide();
	}
}
}
