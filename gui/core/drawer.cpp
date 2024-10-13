#include <gui/core/drawer.h>
#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <imgui/misc/cpp/imgui_stdlib.cpp>

namespace fugui {
namespace {
const char* cstr(std::u8string_view str) {
    return reinterpret_cast<const char*>(str.data());
}
}

ImVec2 Cast(const Vector2& vec) {
	return { vec.x, vec.y };
}

bool Drawer::CheckBox(std::u8string_view label, bool* checked, const Vector2& size) {
	return ImGui::Checkbox(cstr(label), checked);
}

void Drawer::Text(std::u8string_view label, const Vector2& size) {
	return ImGui::Text(cstr(label));
}

bool Drawer::Button(std::u8string_view label, const Vector2& size) {
	return ImGui::Button(cstr(label), Cast(size));
}

bool Drawer::Selectable(std::u8string_view label, bool* is_selected, int flags, const Vector2& size) {
	return ImGui::Selectable(cstr(label), is_selected, flags, Cast(size));
}

struct InputTextCallback_UserData
{
    std::u8string* Str;
    ImGuiInputTextCallback  ChainCallback;
    void* ChainCallbackUserData;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        auto str = user_data->Str;
        IM_ASSERT(data->Buf == (char*)str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

bool Drawer::InputText(std::u8string_view label,
    std::u8string* buffer,
    int flags,
    const Vector2& size)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = buffer;
    cb_user_data.ChainCallback = nullptr;
    cb_user_data.ChainCallbackUserData = nullptr;

    return ImGui::InputText(
        cstr(label),
        (char*)buffer->c_str(),
        buffer->capacity() + 1,
        flags,
        InputTextCallback,
        &cb_user_data);
}

bool Drawer::BeginWindow(std::u8string_view title, bool* open, int flags) {
	return ImGui::Begin(cstr(title), open, flags);
}

void Drawer::EndWindow() {
	ImGui::End();
}
bool Drawer::BeginListBox(std::u8string_view label, const Vector2& size)
{
	return ImGui::BeginListBox(cstr(label), Cast(size));
}

void Drawer::EndListBox() {
	ImGui::EndListBox();
}

bool Drawer::BeginTable(std::u8string_view label, size_t column, int flags, const Vector2& size, float inner_width) {
	return ImGui::BeginTable(cstr(label), static_cast<int>(column), flags, Cast(size), inner_width);
}

void Drawer::EndTable() {
	ImGui::EndTable();
}
}
