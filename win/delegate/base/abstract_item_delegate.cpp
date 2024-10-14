#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
AbstractItemDelegate::AbstractItemDelegate()
	: Object{nullptr, u8"Delegate", ObjectType::Delegate}
{
}
}
