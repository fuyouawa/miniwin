#include <miniwin/widgets/file_dialog.h>

#include <Windows.h>

#include <thread>
#include <mutex>

#include <miniwin/core/imgui.h>
#include <miniwin/tools/regex.h>
#include <miniwin/tools/stringlist.h>

namespace miniwin {
namespace {
String OpenFileDialog(Window* parent, const String& capacity, const String& dir, const String& filter,
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

	OPENFILENAMEA ofn;

	char file[MAX_PATH]{0};
	ZeroMemory(&ofn, sizeof(ofn));
	if (parent) {
		ofn.hwndOwner = reinterpret_cast<HWND>(parent->PlatformHandle());
	}
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = file;
	ofn.nMaxFile = sizeof(file);
	ofn.lpstrFilter = windows_filter.data();
	ofn.lpstrTitle = capacity.data();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn)) {
		*selected_filter = filters[ofn.nFilterIndex == 0 ? 0 : ofn.nFilterIndex - 1];
		return ofn.lpstrFile;
	}
	return {};
}
}

class FileDialog::Impl {
public:
	Impl(FileDialog* owner, const Config& cfg) : owner_(owner), cfg_(cfg) {}

	void Init() {
		owner_->SetTitle("Select File...");
		owner_->SetId("FileDialog");
		owner_->EnableFlags(imgui::kWindowNoInputs
		                  | imgui::kWindowNoBackground
		                  | imgui::kWindowNoTitleBar, true);
		owner_->SetSize({});
	}

	void DoOpenFileDialog() {
		if (!open_file_dialog_thread_.joinable()) {
			open_file_dialog_thread_ = std::thread([cfg = cfg_,cap = owner_->Title(), this]() {
				String sf;
				auto f = OpenFileDialog(
					cfg.parent,
					cap,
					cfg.directory,
					cfg.filter,
					&sf);

				{
					std::lock_guard lk(mutex_);
					file_ = std::move(f);
					selected_filter = std::move(sf);
				}
				selected_ = true;
				cfg.selected_callback(owner_);
			});
		}
	}

	FileDialog* owner_;
	std::thread open_file_dialog_thread_;
	std::atomic_bool selected_;
	String selected_filter;
	String file_;
	std::mutex mutex_;
	Config cfg_;
};

void FileDialog::GetOpenFileNameAsync(Window* parent, const String& capacity, GetOpenFileNameCallback callback,
                                      const String& dir, const String& filter) {
	Config cfg(parent, dir, filter, [cb = std::move(callback)](FileDialog* dlg) {
		cb(std::move(dlg->impl_->file_), std::move(dlg->impl_->selected_filter));
		dlg->Close();
	});

	auto dlg = new FileDialog(cfg);
	dlg->SetTitle(capacity);
	dlg->Open();
}

FileDialog::FileDialog(const Config& cfg)
	: Dialog(cfg.parent) {
	impl_ = std::make_unique<Impl>(this, cfg);
	impl_->Init();
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

void FileDialog::OnPaintWindowBegin() {
	Dialog::OnPaintWindowBegin();

	impl_->DoOpenFileDialog();

	if (impl_->selected_) {
		Hide();
	}
}
}
