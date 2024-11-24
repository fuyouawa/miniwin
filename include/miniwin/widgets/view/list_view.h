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

	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;
	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Awake() override;
    void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}