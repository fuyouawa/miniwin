#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ListView : public AbstractItemView {
public:
    ListView(Widget* parent, std::u8string_view label);
    ~ListView() override;

	std::u8string_view label() const;
	void set_label(std::u8string_view label);

protected:
    void PaintBegin() override;

	_MW_IMPL
};
}