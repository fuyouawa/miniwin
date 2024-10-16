#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
AbstractItemDelegate::AbstractItemDelegate(Object* parent)
	: Object{parent, u8"Delegate", ObjectType::Delegate}
{
}
}
