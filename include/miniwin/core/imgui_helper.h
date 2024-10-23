#pragma once
#include <string>
#include <miniwin/tools/container.h>
#include <miniwin/core/imgui_flags.h>

namespace miniwin {
class ImGuiHelper
{
public:
	class ListClipper
	{
	public:
		ListClipper();
		~ListClipper();

		void Begin(size_t items_count, float items_height = -1);
		bool Step();
		void End();

		size_t display_start() const;
		size_t display_end() const;

	private:
		class Impl;
		Impl* impl_;
	};

    static bool IsWindowDocked();

	static void PushID(int id);
	static void PushID(const void* id);
	static void PushID(std::u8string_view id);
    static void PopID();

	static void BeginDisabled(bool disabled = true);
	static void EndDisabled();

	static Vector2 GetItemRectSize();
	static void SetNextItemWidth(float item_width);
	static void PushStyleVar(ImGuiFlags::StyleVar idx, float val);
	static void PushStyleVar(ImGuiFlags::StyleVar idx, Vector2 val);

	static bool IsWindowCollapsed();
	static void SetWindowCollapsed(bool collapsed, ImGuiFlags::Cond cond = ImGuiFlags::kCondNone);

	static bool CheckBox(
		std::u8string_view label,
		bool* checked
	);

	static void Text(
		std::u8string_view label
	);

	static bool Button(
		std::u8string_view label,
		const Vector2& size = {}
	);

	static bool Selectable(
		std::u8string_view label,
		bool* is_selected,
		FlagsType flags = 0,
		const Vector2& size = {}
	);

	static bool InputText(
		std::u8string_view label,
		std::u8string* buffer,
		FlagsType flags = 0
	);

	static bool BeginWindow(
		std::u8string_view title,
		bool* open,
		FlagsType flags = 0
	);


    static bool BeginTable(
        std::u8string_view id,
        size_t column,
		FlagsType flags = 0,
        const Vector2& size = { 0, 0 },
        float inner_width = 0.0f
    );

    static void TableSetupColumn(
        std::u8string_view label,
		FlagsType flags = 0,
        float init_width_or_weight = 0,
        uint32_t user_id = 0);

    static void TableHeader(std::u8string_view label);

    static bool TableSetColumnIndex(size_t column_n);

    static void TableNextRow(
		FlagsType flags = 0,
		float row_min_height = 0);

    static void EndTable();

	static void EndWindow();

	static bool BeginCombo(
		std::u8string_view label,
		std::u8string_view preview_value,
		FlagsType flags = 0);

	static void EndCombo();

	static bool BeginListBox(std::u8string_view label, const Vector2& size);
	static void EndListBox();

	static void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);

	static bool BeginChildWindow(
		std::u8string_view id,
		const Vector2& size = { 0, 0 },
		int child_window_flags = 0,
		int window_flags = 0);

	static void EndChildWindow();
};
}
