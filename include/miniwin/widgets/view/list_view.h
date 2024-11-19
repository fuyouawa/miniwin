#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class ListView : public AbstractItemView {
	MW_OBJECT
public:
    ListView();
    ~ListView() override;

	String RightLabel() const;
	void SetRightLabel(const String& label);

	//TODO Calc

protected:
	void Awake() override;
    void PaintBegin(size_t index) override;

	_MW_IMPL
};
}