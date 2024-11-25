#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class ComboBoxView : public AbstractItemView {
	MW_OBJECT
public:
	ComboBoxView();
	~ComboBoxView() override;

	String Text() const;
	void SetText(const String& text);

	Vector2D Size() const override;
	void SetSize(const Vector2D& size) override;

protected:
	void Awake() override;
	void PaintBegin(size_t index) override;
	void PaintEnd(size_t index) override;

	_MW_IMPL
};
}