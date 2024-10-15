#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>

namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent);
    ~TableView() override;

    _MW_IMPL
};
}
