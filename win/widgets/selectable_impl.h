#pragma once
#include <miniwin/widgets/selectable.h>

namespace miniwin {
class Selectable::Impl {
public:
    Impl(Selectable* owner);

    Selectable* owner_;
    SelectableFlags flags_;
    bool cur_selected_ = false;
    bool prev_selected_ = false;
};
}
