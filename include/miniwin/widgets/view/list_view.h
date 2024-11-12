#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ListView : public AbstractItemView {
public:
    ListView(Widget* parent, const String& text);
    ~ListView() override;

	const String& Text() const;
	void SetText(const String& text);

protected:
    void PaintBegin() override;

	_MW_IMPL
};
}