#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ListView : public AbstractItemView {
public:
    ListView(Widget* parent, std::u8string_view text);
    ~ListView() override;

	std::u8string_view Text() const;
	void SetText(std::u8string_view text);

protected:
    void PaintBegin() override;

	_MW_IMPL
};
}