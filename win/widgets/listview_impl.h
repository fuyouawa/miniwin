#pragma once
#include <miniwin/widgets/listview.h>
#include <miniwin/core/imgui_helper.h>

namespace miniwin {
class ListView::Impl
{
public:
	Impl(ListView* owner);

	void Init();

	ListView* owner_;
	ImGuiHelper::ListClipper clipper_;
};
}
