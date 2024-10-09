#pragma once
#include <fugui/widgets/view/base/abstract_item_view.h>

namespace fugui {
class ListView : public AbstractItemView
{
public:
	ListView(Widget* const parent, std::u8string_view label, bool show = true);

protected:
	void OnItemShowablePaintBegin() override;
	void OnItemShowablePaintEnd() override;

	bool listbox_open_;
};
}