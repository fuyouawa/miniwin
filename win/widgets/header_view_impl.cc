#include "header_view_impl.h"

namespace miniwin {
HeaderView::Impl::Impl(HeaderView* owner, Orientation orientation):
	owner_(owner), orientation_(orientation)
{
}
}
