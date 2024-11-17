#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
class AbstractItemDelegate : public Object {
	MW_OBJECT
public:
	AbstractItemDelegate();

	void Initialize(const SharedObject& parent) override;

	virtual void Paint(const SharedItemView& view, const ModelIndex& index) = 0;
};
}
