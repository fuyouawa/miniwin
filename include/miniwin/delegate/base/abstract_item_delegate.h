#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
class AbstractItemDelegate : public Object {
	MW_OBJECT
public:
	AbstractItemDelegate();
	~AbstractItemDelegate() override;

	void Paint(const SharedItemView& view, const ModelIndex& index);

protected:
	virtual void PaintBegin(const SharedItemView& view, const ModelIndex& index);
	virtual void PaintEnd(const SharedItemView& view, const ModelIndex& index);

	_MW_IMPL
};
}
