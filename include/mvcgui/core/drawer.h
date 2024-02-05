#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include <functional>
#include <mvcgui/tools/container.h>
#include <mvcgui/model/base/abstract_list_model.h>

namespace mvcgui {
class Drawer
{
public:
	struct InputTextCallbackData {
		//TODO InputTextCallbackDataÌî³ä×Ö¶Î
	};
	using InputTextCallback = std::function<int(const InputTextCallbackData&)>;

	static bool CheckBox(
		std::u8string_view label,
		bool* checked,
		const Vector2& size = Vector2::Zero
	);

	static bool ComboBox(
		std::u8string_view label,
		AbstractListModelPtr model,
		ModelIndex* cur_index,
		int flags = 0,
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
		std::vector<char8_t>& buffer,
		const InputTextCallback& cb,
		int flags = 0,
		const Vector2& size = Vector2::Zero
	);

	static bool BeginWindow(
		std::u8string_view title,
		bool* open,
		int flags = 0,
		const Vector2& size = Vector2::Zero
	);

	static void EndWindow();

	static bool BeginListBox(
		std::u8string_view label,
		const Vector2& size = Vector2::Zero
	);

	static void EndListBox();
};
}