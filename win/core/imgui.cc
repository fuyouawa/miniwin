#include <miniwin/core/imgui.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <miniwin/core/widgetid_pool.h>
#include "win/tools/debug.h"
#include "imgui_cast.h"

namespace miniwin {
namespace imgui {
namespace {
struct InputTextCallbackImplUserData {
	String* Str;
	InputTextCallback callback;
};

int InputTextCallbackImpl(ImGuiInputTextCallbackData* data) {
	auto user_data = static_cast<InputTextCallbackImplUserData*>(data->UserData);
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
		// Resize string callback
		// If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
		auto str = user_data->Str;
		IM_ASSERT(data->Buf == str->data());
		str->resize(data->BufTextLen);
		data->Buf = str->data();
	}
	else if (user_data->callback) {
		// Forward to user callback, if any
		return user_data->callback(InputTextCallbackData(data)) ? 0 : 1;
	}
	return 0;
}

String CombineId(const String& text, WidgetId id) {
	return text + "###" + String::FromInteger(id);
}
}


class ListClipper::Impl {
public:
	ImGuiListClipper clipper_;
};

ListClipper::ListClipper() {
	impl_ = std::make_unique<Impl>();
}

ListClipper::~ListClipper() {}

void ListClipper::Begin(size_t items_count, float items_height) {
	impl_->clipper_.Begin(static_cast<int>(items_count), items_height);
}

bool ListClipper::Step() {
	return impl_->clipper_.Step();
}

void ListClipper::End() {
	impl_->clipper_.End();
}

size_t ListClipper::display_start() const {
	return impl_->clipper_.DisplayStart;
}

size_t ListClipper::display_end() const {
	return impl_->clipper_.DisplayEnd;
}

WidgetIdScope::WidgetIdScope(Mode mode, WidgetId id) : mode_(mode) {
	switch (mode_) {
	case kAutoAlloc:
		id_ = WidgetIdPool::Instance().AllocId();
		break;
	default:
		id_ = id;
		break;
	}
	PushID(id_);
}

WidgetIdScope::~WidgetIdScope() {
	PopID();
	switch (mode_) {
	case kAutoAlloc:
		WidgetIdPool::Instance().RecycleId(id_);
		break;
	default:
		id_ = 0;
		break;
	}
}

InputTextCallbackData::InputTextCallbackData(void* impl_data) : impl_data_(impl_data) {}

InputTextFlags InputTextCallbackData::EventFlag() const {
	return static_cast<InputTextFlags>(reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_)->EventFlag);
}

KeyCode InputTextCallbackData::InputKey() const {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return static_cast<KeyCode>(p->EventKey);
}

wchar_t InputTextCallbackData::InputChar() const {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return p->EventChar;
}

void InputTextCallbackData::SetInputChar(wchar_t ch) {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	p->EventChar = ch;
}

size_t InputTextCallbackData::CursorPos() const {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return p->CursorPos;
}

void InputTextCallbackData::SetCursorPos(size_t pos) {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	p->CursorPos = pos;
}

size_t InputTextCallbackData::TextLength() {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return p->BufTextLen;
}

Vector2DInt InputTextCallbackData::Selection() const {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return { p->SelectionStart, p->SelectionEnd };
}

void InputTextCallbackData::SetSelection(const Vector2DInt& range) {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	p->SelectionStart = range.x();
	p->SelectionEnd = range.y();
}

void InputTextCallbackData::SelectAll() {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	p->SelectAll();
}

void InputTextCallbackData::ClearSelection() {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	p->ClearSelection();
}

bool InputTextCallbackData::HasSelection() const {
	auto p = reinterpret_cast<ImGuiInputTextCallbackData*>(impl_data_);
	return p->HasSelection();
}


bool IsWindowDocked() {
	return ImGui::IsWindowDocked();
}

void PushID(int id) {
	ImGui::PushID(id);
}

void PushID(const void* id) {
	ImGui::PushID(id);
}

void PushID(const String& id) {
	ImGui::PushID(id.data());
}

void PopID() {
	ImGui::PopID();
}

void BeginDisabled(bool disabled) {
	ImGui::BeginDisabled(disabled);
}

void EndDisabled() {
	ImGui::EndDisabled();
}

Vector2D GetItemRectSize() {
	return CastFromIm(ImGui::GetItemRectSize());
}

Vector2D GetWindowSize() {
	return CastFromIm(ImGui::GetWindowSize());
}

Vector2D GetWindowPos() {
	return CastFromIm(ImGui::GetWindowPos());
}

void SetCursorPos(const Vector2D& pos) {
	ImGui::SetCursorPos(CastToIm(pos));
}

void SetCursorPosX(float x) {
	ImGui::SetCursorPosX(x);
}

void SetCursorPosY(float y) {
	ImGui::SetCursorPosY(y);
}

Vector2D GetCursorPos() {
	return CastFromIm(ImGui::GetCursorPos());
}

float GetCursorPosX() {
	return ImGui::GetCursorPosX();
}

float GetCursorPosY() {
	return ImGui::GetCursorPosY();
}

Vector2D CalcTextSize(const String& text, bool hide_text_after_double_hash, float wrap_width) {
	return CastFromIm(ImGui::CalcTextSize(text.data(), text.data() + text.size(), hide_text_after_double_hash,
	                                      wrap_width));
}

void PushItemWidth(float item_width) {
	ImGui::PushItemWidth(item_width);
}

void PopItemWidth() {
	ImGui::PopItemWidth();
}

void SetNextItemWidth(float item_width) {
	ImGui::SetNextItemWidth(item_width);
}

void SetNextWindowPos(const Vector2D& pos, Cond cond, const Vector2D& pivot) {
	ImGui::SetNextWindowPos(CastToIm(pos), cond, CastToIm(pivot));
}

void SetNextWindowSize(const Vector2D& size, Cond cond) {
	ImGui::SetNextWindowSize(CastToIm(size), cond);
}

void PushStyleVar(StyleVar idx, float val) {
	ImGui::PushStyleVar(idx, val);
}

void PushStyleVar(StyleVar idx, Vector2D val) {
	ImGui::PushStyleVar(idx, CastToIm(val));
}

void PopStyleVar(size_t count) {
	ImGui::PopStyleVar(count);
}

bool IsWindowCollapsed() {
	return ImGui::IsWindowCollapsed();
}

void SetWindowCollapsed(bool collapsed, Cond cond) {
	ImGui::SetWindowCollapsed(collapsed, cond);
}

void Dummy(const Vector2D& size) {
	ImGui::Dummy(CastToIm(size));
}

bool CheckBox(const String& label, bool* checked) {
	return ImGui::Checkbox(label.data(), checked);
}

void Text(const String& label) {
	return ImGui::Text(label.data());
}

bool Button(const String& label, const Vector2D& size) {
	return ImGui::Button(label.data(), CastToIm(size));
}

bool Selectable(const String& label, bool* is_selected, FlagsType flags, const Vector2D& size) {
	return ImGui::Selectable(
		label.data(),
		is_selected,
		flags,
		CastToIm(size));
}

bool InputText(const String& label, String* buffer, FlagsType flags, const Vector2D& size,
               InputTextCallback callback) {
	flags |= kInputTextCallbackResize;

	InputTextCallbackImplUserData cb_user_data;
	cb_user_data.Str = buffer;
	cb_user_data.callback = std::move(callback);

	PushItemWidth(size.x());
	return ImGui::InputText(
		label.data(),
		buffer->data(),
		buffer->capacity() + 1,
		flags,
		InputTextCallbackImpl,
		&cb_user_data);
}

bool BeginWindow(const String& title, WidgetId id, bool* open, FlagsType flags) {
	return BeginWindow(CombineId(title, id), open, flags);
}

bool BeginWindow(const String& name, bool* open, FlagsType flags) {
	return ImGui::Begin(name.data(), open, flags);
}

void EndWindow() {
	ImGui::End();
}

bool IsPopupOpen(const String& title, WidgetId id, FlagsType flags) {
	return IsPopupOpen(CombineId(title, id), flags);
}

void OpenPopup(const String& title, WidgetId id, FlagsType flags) {
	OpenPopup(CombineId(title, id), flags);
}

bool IsPopupOpen(const String& name, FlagsType flags) {
	return ImGui::IsPopupOpen(name.data(), flags);
}

void OpenPopup(const String& name, FlagsType flags) {
	ImGui::OpenPopup(name.data(), flags);
}

bool BeginPopupModal(const String& name, bool* open, FlagsType flags) {
	return ImGui::BeginPopupModal(name.data(), open, flags);
}

void CloseCurrentPopup() {
	ImGui::CloseCurrentPopup();
}

bool BeginPopupModal(const String& title, WidgetId id, bool* open, FlagsType flags) {
	return BeginPopupModal(CombineId(title, id), open, flags);
}

void EndPopup() {
	ImGui::EndPopup();
}

bool BeginCombo(const String& label, const String& preview_value, FlagsType flags, const Vector2D& size) {
	if (size.x() > 0) {
		SetNextItemWidth(size.x());
	}
	return ImGui::BeginCombo(label.data(), preview_value.data(), flags);
}

void EndCombo() {
	ImGui::EndCombo();
}

bool BeginListBox(const String& label, const Vector2D& size) {
	return ImGui::BeginListBox(label.data(), CastToIm(size));
}

void EndListBox() {
	ImGui::EndListBox();
}

void SameLine(float offset_from_start_x, float spacing) {
	ImGui::SameLine(offset_from_start_x, spacing);
}

bool BeginChildWindow(WidgetId id, const Vector2D& size, int child_window_flags,
                      int window_flags) {
	return ImGui::BeginChild(id, CastToIm(size), child_window_flags, window_flags);
}

void EndChildWindow() {
	return ImGui::EndChild();
}

Vector2D GetContentRegionAvail() {
	return CastFromIm(ImGui::GetContentRegionAvail());
}

bool BeginTable(const String& id, size_t column, FlagsType flags, const Vector2D& size, float inner_width) {
	return ImGui::BeginTable(id.data(), static_cast<int>(column), flags, CastToIm(size), inner_width);
}

void EndTable() {
	ImGui::EndTable();
}

void SetNextWindowBgAlpha(float alpha) {
	ImGui::SetNextWindowBgAlpha(alpha);
}

void TableSetupColumn(const String& label, FlagsType flags, float init_width_or_weight, uint32_t user_id) {
	return ImGui::TableSetupColumn(label.data(), flags, init_width_or_weight, user_id);
}

void TableHeader(const String& label) {
	ImGui::TableHeader(label.data());
}

bool TableSetColumnIndex(size_t column_n) {
	return ImGui::TableSetColumnIndex(static_cast<int>(column_n));
}

void TableNextRow(FlagsType row_flags, float row_min_height) {
	ImGui::TableNextRow(row_flags, row_min_height);
}

namespace style {
Vector2D FramePadding() {
	return CastFromIm(ImGui::GetStyle().FramePadding);
}

Vector2D ItemSpacing() {
	return CastFromIm(ImGui::GetStyle().ItemSpacing);
}
}
}
}
