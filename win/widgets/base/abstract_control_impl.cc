#include "abstract_control_impl.h"

namespace miniwin {
AbstractControl::Impl::Impl(AbstractControl* owner)
	: owner_(owner)
{
}

void AbstractControl::Impl::PaintEnd()
{
}

void AbstractControl::Impl::PaintBegin()
{
}
}
