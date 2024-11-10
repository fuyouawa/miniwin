#include <miniwin/core/imgui_helper.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace {
struct InputTextCallbackUserData
{
    String* Str;
    ImGuiInputTextCallback ChainCallback;
    void* ChainCallbackUserData;
};

int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    auto user_data = static_cast<InputTextCallbackUserData*>(data->UserData);
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        auto str = user_data->Str;
        IM_ASSERT(data->Buf == str->data());
        str->resize(data->BufTextLen);
        data->Buf = str->data();
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

ImVec2 CastToIm(const Vector2D& vec) {
    return { vec.x(), vec.y() };
}
Vector2D CastFromIm(const ImVec2& vec) {
    return { vec.x, vec.y };
}
}


class ImGuiHelper::ListClipper::Impl
{
public:
    ImGuiListClipper clipper_;
};

ImGuiHelper::ListClipper::ListClipper()
{
    impl_ = new Impl();
}

ImGuiHelper::ListClipper::~ListClipper()
{
    delete impl_;
}

void ImGuiHelper::ListClipper::Begin(size_t items_count, float items_height)
{
    impl_->clipper_.Begin(static_cast<int>(items_count), items_height);
}

bool ImGuiHelper::ListClipper::Step()
{
    return impl_->clipper_.Step();
}

void ImGuiHelper::ListClipper::End()
{
    impl_->clipper_.End();
}

size_t ImGuiHelper::ListClipper::display_start() const
{
    return impl_->clipper_.DisplayStart;
}

size_t ImGuiHelper::ListClipper::display_end() const
{
    return impl_->clipper_.DisplayEnd;
}

bool ImGuiHelper::IsWindowDocked()
{
    return ImGui::IsWindowDocked();
}

void ImGuiHelper::PushID(int id)
{
    ImGui::PushID(id);
}

void ImGuiHelper::PushID(const void* id)
{
    ImGui::PushID(id);
}

void ImGuiHelper::PushID(const String& id)
{
    ImGui::PushID(id.data());
}

void ImGuiHelper::PopID()
{
    ImGui::PopID();
}

void ImGuiHelper::BeginDisabled(bool disabled)
{
    ImGui::BeginDisabled(disabled);
}

void ImGuiHelper::EndDisabled()
{
    ImGui::EndDisabled();
}

Vector2D ImGuiHelper::GetItemRectSize()
{
    return CastFromIm(ImGui::GetItemRectSize());
}

void ImGuiHelper::SetNextItemWidth(float item_width)
{
    ImGui::SetNextItemWidth(item_width);
}

void ImGuiHelper::PushStyleVar(ImGuiFlags::StyleVar idx, float val)
{
    ImGui::PushStyleVar(idx, val);
}

void ImGuiHelper::PushStyleVar(ImGuiFlags::StyleVar idx, Vector2D val)
{
    ImGui::PushStyleVar(idx, CastToIm(val));
}

bool ImGuiHelper::IsWindowCollapsed()
{
    return ImGui::IsWindowCollapsed();
}

void ImGuiHelper::SetWindowCollapsed(bool collapsed, ImGuiFlags::Cond cond)
{
    ImGui::SetWindowCollapsed(collapsed, cond);
}

void ImGuiHelper::Dummy(const Vector2D& size)
{
    ImGui::Dummy(CastToIm(size));
}

bool ImGuiHelper::CheckBox(const String& label, bool* checked) {
	return ImGui::Checkbox(label.data(), checked);
}

void ImGuiHelper::Text(const String& label) {
	return ImGui::Text(label.data());
}

bool ImGuiHelper::Button(const String& label, const Vector2D& size) {
	return ImGui::Button(label.data(), CastToIm(size));
}

bool ImGuiHelper::Selectable(const String& label, bool* is_selected, FlagsType flags, const Vector2D& size) {
	return ImGui::Selectable(
        label.data(),
        is_selected,
        flags,
        CastToIm(size));
}

bool ImGuiHelper::InputText(const String& label,
    String* buffer,
    FlagsType flags)
{
    MW_ASSERT_X((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags = flags | ImGuiInputTextFlags_CallbackResize;

    InputTextCallbackUserData cb_user_data;
    cb_user_data.Str = buffer;
    cb_user_data.ChainCallback = nullptr;
    cb_user_data.ChainCallbackUserData = nullptr;

    return ImGui::InputText(
        label.data(),
        buffer->data(),
        buffer->capacity() + 1,
        flags,
        InputTextCallback,
        &cb_user_data);
}

bool ImGuiHelper::BeginWindow(const String& title, bool* open, FlagsType flags) {
	return ImGui::Begin(title.data(), open, flags);
}

void ImGuiHelper::EndWindow() {
	ImGui::End();
}

bool ImGuiHelper::BeginCombo(const String& label, const String& preview_value, FlagsType flags)
{
    return ImGui::BeginCombo(label.data(), preview_value.data(), flags);
}

void ImGuiHelper::EndCombo()
{
    ImGui::EndCombo();
}

bool ImGuiHelper::BeginListBox(const String& label, const Vector2D& size)
{
    return ImGui::BeginListBox(label.data(), CastToIm(size));
}

void ImGuiHelper::EndListBox()
{
    ImGui::EndListBox();
}

void ImGuiHelper::SameLine(float offset_from_start_x, float spacing)
{
    ImGui::SameLine(offset_from_start_x, spacing);
}

bool ImGuiHelper::BeginChildWindow(const String& id, const Vector2D& size, int child_window_flags,
    int window_flags)
{
    return ImGui::BeginChild(id.data(), CastToIm(size), child_window_flags, window_flags);
}

void ImGuiHelper::EndChildWindow()
{
    return ImGui::EndChild();
}

bool ImGuiHelper::BeginTable(const String& id, size_t column, FlagsType flags, const Vector2D& size, float inner_width) {
	return ImGui::BeginTable(id.data(), static_cast<int>(column), flags, CastToIm(size), inner_width);
}

void ImGuiHelper::EndTable() {
	ImGui::EndTable();
}

void ImGuiHelper::TableSetupColumn(const String& label, FlagsType flags, float init_width_or_weight, uint32_t user_id)
{
    return ImGui::TableSetupColumn(label.data(), flags, init_width_or_weight, user_id);
}

void ImGuiHelper::TableHeader(const String& label)
{
    ImGui::TableHeader(label.data());
}

bool ImGuiHelper::TableSetColumnIndex(size_t column_n)
{
    return ImGui::TableSetColumnIndex(static_cast<int>(column_n));
}

void ImGuiHelper::TableNextRow(FlagsType row_flags, float row_min_height)
{
    ImGui::TableNextRow(row_flags, row_min_height);
}
}
