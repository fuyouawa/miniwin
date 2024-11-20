#pragma once
#include <miniwin/tools/vector2d.h>
#include <miniwin/core/imgui_flags.h>
#include <miniwin/defs.h>
#include <miniwin/tools/string.h>

#include <functional>

namespace miniwin {
namespace imgui {
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

	_MW_IMPL
};

class WidgetIdScope {
public:
	enum Mode {
		/**
		 * 使用WidgetIdPool自动分配id
		 */
		kAutoAlloc,
		/**
		 * 手动指定id
		 */
		kManual
	};

	/**
	 * id作用域，在构造的时候PushID，析构的时候PopID
	 * @param mode 模式
	 * @param id 如果model是kAutoAlloc，则忽略
	 */
	WidgetIdScope(Mode mode = kAutoAlloc, WidgetId id = 0);
	~WidgetIdScope();

	WidgetId id() const { return id_; }
	Mode mode() const { return mode_; }

private:
	WidgetId id_;
	Mode mode_;
};

class InputTextCallbackData {
public:
	InputTextCallbackData(void* impl_data);

	InputTextFlags EventFlag() const;
	wchar_t InputChar() const;
	void SetInputChar(wchar_t ch);

	size_t CursorPos() const;
	void SetCursorPos(size_t pos);

	size_t TextLength();

	Vector2DInt Selection() const;
	void SetSelection(const Vector2DInt& range);

	void SelectAll();
	void ClearSelection();
	bool HasSelection() const;

private:
	void* impl_data_;
};

using InputTextCallback = std::function<bool(InputTextCallbackData data)>;

bool IsWindowDocked();

void PushID(int id);
void PushID(const void* id);
void PushID(const String& id);
void PopID();

void BeginDisabled(bool disabled = true);
void EndDisabled();

Vector2D GetItemRectSize();
Vector2D GetWindowSize();
Vector2D GetWindowPos();

void SetCursorPos(const Vector2D& pos);
void SetCursorPosX(float x);
void SetCursorPosY(float y);
Vector2D GetCursorPos();
float GetCursorPosX();
float GetCursorPosY();

Vector2D CalcTextSize(const String& text, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);

void PushItemWidth(float item_width);
void PopItemWidth();

void SetNextItemWidth(float item_width);
void SetNextWindowPos(const Vector2D& pos, Cond cond = kCondNone, const Vector2D& pivot = {});
void SetNextWindowSize(const Vector2D& size, Cond cond = kCondNone);

void PushStyleVar(StyleVar idx, float val);
void PushStyleVar(StyleVar idx, Vector2D val);
void PopStyleVar(size_t count = 1);

bool IsWindowCollapsed();
void SetWindowCollapsed(bool collapsed, Cond cond = kCondNone);

Vector2D GetContentRegionAvail();
void SetNextWindowBgAlpha(float alpha);

void Dummy(const Vector2D& size);

bool CheckBox(
	const String& label,
	bool* checked
);

void Text(const String& label);

bool Button(
	const String& label,
	const Vector2D& size = {}
);

bool Selectable(
	const String& label,
	bool* is_selected,
	FlagsType flags = 0,
	const Vector2D& size = {}
);

bool InputText(
	const String& label,
	String* buffer,
	FlagsType flags = 0,
	const Vector2D& size = {},
	InputTextCallback callback = {}
);


bool BeginTable(
	const String& id,
	size_t column,
	FlagsType flags = 0,
	const Vector2D& size = { 0, 0 },
	float inner_width = 0.0f
);

void TableSetupColumn(
	const String& label,
	FlagsType flags = 0,
	float init_width_or_weight = 0,
	uint32_t user_id = 0);

void TableHeader(const String& label);

bool TableSetColumnIndex(size_t column_n);

void TableNextRow(
	FlagsType flags = 0,
	float row_min_height = 0);

void EndTable();


bool BeginWindow(
	const String& title,
	WidgetId id,
	bool* open,
	FlagsType flags = 0
);
bool BeginWindow(
	const String& name,
	bool* open,
	FlagsType flags = 0
);

void EndWindow();

bool IsPopupOpen(const String& title, WidgetId id, FlagsType flags = 0);
void OpenPopup(const String& title, WidgetId id, FlagsType flags = 0);

bool IsPopupOpen(const String& name, FlagsType flags = 0);
void OpenPopup(const String& name, FlagsType flags = 0);

void CloseCurrentPopup();

bool BeginPopupModal(
	const String& title,
	WidgetId id,
	bool* open,
	FlagsType flags = 0);

bool BeginPopupModal(
	const String& name,
	bool* open,
	FlagsType flags = 0);

void EndPopup();

bool BeginCombo(
	const String& label,
	const String& preview_value,
	FlagsType flags = 0,
	const Vector2D& size = {});

void EndCombo();

bool BeginListBox(const String& label, const Vector2D& size);
void EndListBox();

void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);

bool BeginChildWindow(
	WidgetId id,
	const Vector2D& size = { 0, 0 },
	int child_window_flags = 0,
	int window_flags = 0);

void EndChildWindow();

namespace style {
Vector2D FramePadding();
Vector2D ItemSpacing();
}
}
}
