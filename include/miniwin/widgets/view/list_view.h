#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class ListView : public AbstractItemView {
	MW_OBJECT
public:
    ListView();
    ~ListView() override;

	String Title() const;
	void SetTitle(const String& title);

protected:
	void Awake() override;
    void PaintBegin() override;

	_MW_IMPL
};
}