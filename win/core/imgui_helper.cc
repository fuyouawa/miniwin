#include <miniwin/core/imgui_helper.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

namespace miniwin {
namespace {
const char* cstr(std::u8string_view str) {
    return reinterpret_cast<const char*>(str.data());
}

struct InputTextCallbackUserData
{
    std::u8string* Str;
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
        IM_ASSERT(data->Buf == reinterpret_cast<const char*>(str->c_str()));
        str->resize(data->BufTextLen);
        data->Buf = reinterpret_cast<char*>(const_cast<char8_t*>(str->c_str()));
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

ImVec2 CastToIm(const Vector2& vec) {
    return { vec.x(), vec.y() };
}
Vector2 CastFromIm(const ImVec2& vec) {
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
    impl_->clipper_.Begin(items_count, items_height);
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

void ImGuiHelper::PushID(std::u8string_view id)
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

Vector2 ImGuiHelper::GetItemRectSize()
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

void ImGuiHelper::PushStyleVar(ImGuiFlags::StyleVar idx, Vector2 val)
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

bool ImGuiHelper::CheckBox(std::u8string_view label, bool* checked) {
	return ImGui::Checkbox(cstr(label), checked);
}

void ImGuiHelper::Text(std::u8string_view label) {
	return ImGui::Text(cstr(label));
}

bool ImGuiHelper::Button(std::u8string_view label, const Vector2& size) {
	return ImGui::Button(cstr(label), CastToIm(size));
}

bool ImGuiHelper::Selectable(std::u8string_view label, bool* is_selected, FlagsType flags, const Vector2& size) {
	return ImGui::Selectable(
        cstr(label),
        is_selected,
        flags,
        CastToIm(size));
}

bool ImGuiHelper::InputText(std::u8string_view label,
    std::u8string* buffer,
    FlagsType flags)
{
    assert((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags = flags | ImGuiInputTextFlags_CallbackResize;

    InputTextCallbackUserData cb_user_data;
    cb_user_data.Str = buffer;
    cb_user_data.ChainCallback = nullptr;
    cb_user_data.ChainCallbackUserData = nullptr;

    return ImGui::InputText(
        cstr(label),
        reinterpret_cast<char*>(const_cast<char8_t*>(buffer->c_str())),
        buffer->capacity() + 1,
        flags,
        InputTextCallback,
        &cb_user_data);
}

bool ImGuiHelper::BeginWindow(std::u8string_view title, bool* open, FlagsType flags) {
	return ImGui::Begin(cstr(title), open, flags);
}

void ImGuiHelper::EndWindow() {
	ImGui::End();
}

bool ImGuiHelper::BeginCombo(std::u8string_view label, std::u8string_view preview_value, FlagsType flags)
{
    return ImGui::BeginCombo(cstr(label), cstr(preview_value), flags);
}

void ImGuiHelper::EndCombo()
{
    ImGui::EndCombo();
}

bool ImGuiHelper::BeginListBox(std::u8string_view label, const Vector2& size)
{
    return ImGui::BeginListBox(cstr(label), CastToIm(size));
}

void ImGuiHelper::EndListBox()
{
    ImGui::EndListBox();
}

void ImGuiHelper::SameLine(float offset_from_start_x, float spacing)
{
    ImGui::SameLine(offset_from_start_x, spacing);
}

bool ImGuiHelper::BeginChildWindow(std::u8string_view id, const Vector2& size, int child_window_flags,
    int window_flags)
{
    return ImGui::BeginChild(cstr(id), CastToIm(size), child_window_flags, window_flags);
}

void ImGuiHelper::EndChildWindow()
{
    return ImGui::EndChild();
}

bool ImGuiHelper::BeginTable(std::u8string_view id, size_t column, FlagsType flags, const Vector2& size, float inner_width) {
	return ImGui::BeginTable(cstr(id), static_cast<int>(column), flags, CastToIm(size), inner_width);
}

void ImGuiHelper::EndTable() {
	ImGui::EndTable();
}

void ImGuiHelper::TableSetupColumn(std::u8string_view label, FlagsType flags, float init_width_or_weight, uint32_t user_id)
{
    return ImGui::TableSetupColumn(cstr(label), flags, init_width_or_weight, user_id);
}

void ImGuiHelper::TableHeader(std::u8string_view label)
{
    ImGui::TableHeader(cstr(label));
}

bool ImGuiHelper::TableSetColumnIndex(size_t column_n)
{
    return ImGui::TableSetColumnIndex(column_n);
}

void ImGuiHelper::TableNextRow(int row_flags, float row_min_height)
{
    ImGui::TableNextRow(row_flags, row_min_height);
}
}
