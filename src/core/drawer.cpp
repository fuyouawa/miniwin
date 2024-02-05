#include <mvcgui/core/drawer.h>
#include <imgui/imgui.h>

namespace mvcgui {
const char* cstr(std::u8string_view str) {
	return reinterpret_cast<const char*>(str.data());
}

ImVec2 Cast(const Vector2& vec) {
	return { vec.x, vec.y };
}

bool Drawer::CheckBox(std::u8string_view label, bool* checked, const Vector2& size) {
	return ImGui::Checkbox(cstr(label), checked);
}

bool Drawer::ComboBox(std::u8string_view label, AbstractListModelPtr model, ModelIndex* cur_index, int flags, const Vector2& size) {
	assert(cur_index->valid() && cur_index->column() == 0);
	auto open = ImGui::BeginCombo(cstr(label), cstr(model->text(*cur_index)), flags);
	if (open)
	{
		for (size_t i = 0; i < model->row_count(); i++) {
			bool is_selected = false;
			if (Drawer::Selectable(model->text(i), &is_selected)) {
				cur_index->set_row(i);
			}
		}
		ImGui::EndCombo();
	}
	return open;
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

bool Drawer::InputText(std::u8string_view label,
	std::vector<char8_t>& buffer,
	const InputTextCallback& cb,
	int flags,
	const Vector2& size)
{
	return ImGui::InputText(cstr(label), (char*)buffer.data(), buffer.size(), flags, [](ImGuiInputTextCallbackData* data) {
		auto& callback = *reinterpret_cast<const InputTextCallback*>(data->UserData);
		InputTextCallbackData mydata{};

		return callback(mydata);
	}, (void*)&cb);
}

bool Drawer::BeginWindow(std::u8string_view title, bool* open, int flags, const Vector2& size) {
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
}