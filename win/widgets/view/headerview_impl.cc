#include "headerview_impl.h"

namespace miniwin {
HeaderView::Impl::Impl(HeaderView* owner, HeaderOrientation orientation):
	owner_(owner), orientation_(orientation)
{
}
}
