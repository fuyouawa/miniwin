#pragma once
#include <miniwin/widgets/view/list_view.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class ListView::Impl
{
public:
	Impl(ListView* owner);

	void Awake();

	ListView* owner_;
	imgui::ListClipper clipper_;
};
}
