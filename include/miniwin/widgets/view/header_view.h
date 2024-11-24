#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/model/base/abstract_item_model.h>

namespace miniwin {
class HeaderView : public AbstractItemView {
	MW_OBJECT
public:
	HeaderView();
	~HeaderView() override;

	HeaderOrientation Orientation() const;
	void SetOrientation(HeaderOrientation orientation);

	virtual void PaintSection(size_t section);
	Vector2D Position() const override;
	void SetPosition(const Vector2D& pos) override;
	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

	//TODO Calc

private:
	using AbstractItemView::SetDrawFlags;

	_MW_IMPL
};

using SharedHeaderView = std::shared_ptr<HeaderView>;
using WeakHeaderView = std::shared_ptr<HeaderView>;
}
