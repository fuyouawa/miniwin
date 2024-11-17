#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
AbstractItemDelegate::AbstractItemDelegate()
{
}

void AbstractItemDelegate::Initialize(const SharedObject& parent) {
	Object::Initialize(parent);
	SetName("Delegate");
}
}
