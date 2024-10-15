#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/header_view.h>

namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent, std::u8string_view id);
    ~TableView() override;

    HeaderView* horizontal_header() const;
    void set_horizontal_header(HeaderView* header_view);

    void PaintBegin() override;
    void PaintEnd() override;

    std::u8string_view id() const;
    void set_id(std::u8string_view id);

    _MW_IMPL
};
}
