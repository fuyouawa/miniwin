#pragma once
#include <miniwin/core/object.h>
#include <miniwin/model/base/model_index.h>

namespace miniwin {
class AbstractItemView;

class AbstractItemDelegate : public Object
{
public:
	AbstractItemDelegate(Object* parent);

	virtual void Paint(AbstractItemView* view, const ModelIndex& index) = 0;
};
}
