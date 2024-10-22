#pragma once
#include <string>
#include <miniwin/tools/container.h>
#include <miniwin/core/flags.h>
#include <miniwin/tools/variant.h>

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

	static bool CheckBox(
		std::u8string_view label,
		bool* checked,
		const Vector2& size = {}
	);

	static void Text(
		std::u8string_view label,
		const Vector2& size = {}
	);

	static bool Button(
		std::u8string_view label,
		const Vector2& size = {}
	);

	static bool Selectable(
		std::u8string_view label,
		bool* is_selected,
		SelectableFlags flags = SelectableFlags::kNone,
		const Vector2& size = {}
	);

	static bool InputText(
		std::u8string_view label,
		std::u8string* buffer,
		InputTextFlags flags = InputTextFlags::kNone,
		const Vector2& size = {}
	);

	static bool BeginWindow(
		std::u8string_view title,
		bool* open,
		WindowFlags flags = WindowFlags::kNone
	);


    static bool BeginTable(
        std::u8string_view id,
        size_t column,
        TableFlags flags = TableFlags::kNone,
        const Vector2& size = { 0, 0 },
        float inner_width = 0.0f
    );

    static void TableSetupColumn(
        std::u8string_view label,
        TableColumnFlags flags = TableColumnFlags::kNone,
        float init_width_or_weight = 0,
        uint32_t user_id = 0);

    static void TableHeader(std::u8string_view label);

    static bool TableSetColumnIndex(size_t column_n);

    static void TableNextRow(TableRowFlags row_flags = TableRowFlags::kNone, float row_min_height = 0);

    static void EndTable();

	static void EndWindow();

	static bool BeginCombo(
		std::u8string_view label,
		std::u8string_view preview_value,
		const Vector2& size = { 0, 0 },
		ComboBoxFlags flags = ComboBoxFlags::kNone);

	static void EndCombo();

	static bool BeginListBox(std::u8string_view label, const Vector2& size);
	static void EndListBox();

	static void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);
};
}
