#pragma once
#include <string>
#include <miniwin/tools/container.h>
#include <miniwin/core/flags.h>

namespace miniwin {
class ImGuiHelper
{
public:
    static bool IsWindowDocked();

    static void PushID(int id);
    static void PushID(const void* id);
    static void PushID(std::string_view id);
    static void PopID();

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
        const Vector2& size = { 0, 200 },
        float inner_width = 0.0f
    );

    static void TableSetupColumn(
        std::u8string_view label,
        TableColumnFlags flags = TableColumnFlags::kNone,
        float init_width_or_weight = 0,
        uint32_t user_id = 0);

    static bool TableSetColumnIndex(size_t column_n);

    static void TableNextRow(TableRowFlags row_flags = TableRowFlags::kNone, float row_min_height = 0);

    static void EndTable();

	static void EndWindow();
};
}
