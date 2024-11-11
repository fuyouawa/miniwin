#include <miniwin/core/imgui.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace imgui {
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


class ListClipper::Impl
{
public:
    ImGuiListClipper clipper_;
};

ListClipper::ListClipper()
{
    impl_ = std::make_unique<Impl>();
}

ListClipper::~ListClipper()
{
}

void ListClipper::Begin(size_t items_count, float items_height)
{
    impl_->clipper_.Begin(static_cast<int>(items_count), items_height);
}

bool ListClipper::Step()
{
    return impl_->clipper_.Step();
}

void ListClipper::End()
{
    impl_->clipper_.End();
}

size_t ListClipper::display_start() const
{
    return impl_->clipper_.DisplayStart;
}

size_t ListClipper::display_end() const
{
    return impl_->clipper_.DisplayEnd;
}

bool IsWindowDocked()
{
    return ImGui::IsWindowDocked();
}

void PushID(int id)
{
    ImGui::PushID(id);
}

void PushID(const void* id)
{
    ImGui::PushID(id);
}

void PushID(const String& id)
{
    ImGui::PushID(id.data());
}

void PopID()
{
    ImGui::PopID();
}

void BeginDisabled(bool disabled)
{
    ImGui::BeginDisabled(disabled);
}

void EndDisabled()
{
    ImGui::EndDisabled();
}

Vector2D GetItemRectSize()
{
    return CastFromIm(ImGui::GetItemRectSize());
}

Vector2D GetWindowSize() {
    return CastFromIm(ImGui::GetWindowSize());
}

Vector2D GetWindowPos() {
    return CastFromIm(ImGui::GetWindowPos());
}

void SetNextItemWidth(float item_width)
{
    ImGui::SetNextItemWidth(item_width);
}

void SetNextWindowPos(const Vector2D& pos, Cond cond, const Vector2D& pivot) {
    ImGui::SetNextWindowPos(CastToIm(pos), cond, CastToIm(pivot));
}

void SetNextWindowSize(const Vector2D& size, Cond cond) {
    ImGui::SetNextWindowSize(CastToIm(size), cond);
}

void PushStyleVar(StyleVar idx, float val)
{
    ImGui::PushStyleVar(idx, val);
}

void PushStyleVar(StyleVar idx, Vector2D val)
{
    ImGui::PushStyleVar(idx, CastToIm(val));
}

bool IsWindowCollapsed()
{
    return ImGui::IsWindowCollapsed();
}

void SetWindowCollapsed(bool collapsed, Cond cond)
{
    ImGui::SetWindowCollapsed(collapsed, cond);
}

void Dummy(const Vector2D& size)
{
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

bool InputText(const String& label,
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

bool BeginWindow(const String& title, bool* open, FlagsType flags) {
    return ImGui::Begin(title.data(), open, flags);
}

void EndWindow() {
    ImGui::End();
}

bool BeginCombo(const String& label, const String& preview_value, FlagsType flags)
{
    return ImGui::BeginCombo(label.data(), preview_value.data(), flags);
}

void EndCombo()
{
    ImGui::EndCombo();
}

bool BeginListBox(const String& label, const Vector2D& size)
{
    return ImGui::BeginListBox(label.data(), CastToIm(size));
}

void EndListBox()
{
    ImGui::EndListBox();
}

void SameLine(float offset_from_start_x, float spacing)
{
    ImGui::SameLine(offset_from_start_x, spacing);
}

bool BeginChildWindow(const String& id, const Vector2D& size, int child_window_flags,
    int window_flags)
{
    return ImGui::BeginChild(id.data(), CastToIm(size), child_window_flags, window_flags);
}

void EndChildWindow()
{
    return ImGui::EndChild();
}

bool BeginTable(const String& id, size_t column, FlagsType flags, const Vector2D& size, float inner_width) {
    return ImGui::BeginTable(id.data(), static_cast<int>(column), flags, CastToIm(size), inner_width);
}

void EndTable() {
    ImGui::EndTable();
}

void TableSetupColumn(const String& label, FlagsType flags, float init_width_or_weight, uint32_t user_id)
{
    return ImGui::TableSetupColumn(label.data(), flags, init_width_or_weight, user_id);
}

void TableHeader(const String& label)
{
    ImGui::TableHeader(label.data());
}

bool TableSetColumnIndex(size_t column_n)
{
    return ImGui::TableSetColumnIndex(static_cast<int>(column_n));
}

void TableNextRow(FlagsType row_flags, float row_min_height)
{
    ImGui::TableNextRow(row_flags, row_min_height);
}
}
}
