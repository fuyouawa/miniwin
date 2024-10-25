#pragma once
#include <miniwin/tools/vector2d.h>
#include <miniwin/core/imgui_flags.h>
#include <miniwin/core/global.h>
#include <miniwin/tools/string.h>

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
	static void PushID(const String& id);
    static void PopID();

	static void BeginDisabled(bool disabled = true);
	static void EndDisabled();

	static Vector2D GetItemRectSize();
	static void SetNextItemWidth(float item_width);
	static void PushStyleVar(ImGuiFlags::StyleVar idx, float val);
	static void PushStyleVar(ImGuiFlags::StyleVar idx, Vector2D val);

	static bool IsWindowCollapsed();
	static void SetWindowCollapsed(bool collapsed, ImGuiFlags::Cond cond = ImGuiFlags::kCondNone);

	static void Dummy(const Vector2D& size);

	static bool CheckBox(
		const String& label,
		bool* checked
	);

	static void Text(
		const String& label
	);

	static bool Button(
		const String& label,
		const Vector2D& size = {}
	);

	static bool Selectable(
		const String& label,
		bool* is_selected,
		FlagsType flags = 0,
		const Vector2D& size = {}
	);

	static bool InputText(
		const String& label,
		String* buffer,
		FlagsType flags = 0
	);

	static bool BeginWindow(
		const String& title,
		bool* open,
		FlagsType flags = 0
	);


    static bool BeginTable(
        const String& id,
        size_t column,
		FlagsType flags = 0,
        const Vector2D& size = { 0, 0 },
        float inner_width = 0.0f
    );

    static void TableSetupColumn(
        const String& label,
		FlagsType flags = 0,
        float init_width_or_weight = 0,
        uint32_t user_id = 0);

    static void TableHeader(const String& label);

    static bool TableSetColumnIndex(size_t column_n);

    static void TableNextRow(
		FlagsType flags = 0,
		float row_min_height = 0);

    static void EndTable();

	static void EndWindow();

	static bool BeginCombo(
		const String& label,
		const String& preview_value,
		FlagsType flags = 0);

	static void EndCombo();

	static bool BeginListBox(const String& label, const Vector2D& size);
	static void EndListBox();

	static void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);

	static bool BeginChildWindow(
		const String& id,
		const Vector2D& size = { 0, 0 },
		int child_window_flags = 0,
		int window_flags = 0);

	static void EndChildWindow();
};
}
