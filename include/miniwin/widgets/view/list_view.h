#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ListView : public AbstractItemView {
	MW_OBJECT
public:
    ListView();
    ~ListView() override;

	String RightLabel() const;
	void SetRightLabel(const String& label);

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Awake() override;
    void BeginUpdate(size_t index) override;
	void EndUpdate(size_t index) override;

	_MW_IMPL
};
}