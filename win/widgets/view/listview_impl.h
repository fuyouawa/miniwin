#pragma once
#include <miniwin/widgets/view/listview.h>

#include <miniwin/core/imgui.h>

namespace miniwin {
class ListView::Impl
{
public:
	Impl(ListView* owner);

	void Init();

	ListView* owner_;
	imgui::ListClipper clipper_;
};
}
