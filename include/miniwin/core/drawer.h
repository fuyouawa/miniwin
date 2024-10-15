#pragma once
#include <string>
#include <miniwin/tools/container.h>

namespace miniwin {
class Drawer
{
public:
	static bool CheckBox(
		std::u8string_view label,
		bool* checked,
		const Vector2& size = Vector2::Zero
	);

	static void Text(
		std::u8string_view label,
		const Vector2& size = Vector2::Zero
	);

	static bool Button(
		std::u8string_view label,
		const Vector2& size = Vector2::Zero
	);

	static bool Selectable(
		std::u8string_view label,
		bool* is_selected,
		int flags = 0,
		const Vector2& size = Vector2::Zero
	);

	static bool InputText(
		std::u8string_view label,
		std::u8string* buffer,
		int flags = 0,
		const Vector2& size = Vector2::Zero
	);

	static bool BeginWindow(
		std::u8string_view title,
		bool* open,
		int flags = 0
	);


    static bool BeginTable(
        std::u8string_view id,
        size_t column,
        int flags = 0,
        const Vector2& size = { 0, 200 },
        float inner_width = 0.0f
    );

    static void EndTable();

	static void EndWindow();
};
}
