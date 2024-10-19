#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/header_view.h>


namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent, std::u8string_view id);
    ~TableView() override;

    HeaderView* HorizontalHeader() const;
    void SetHorizontalHeader(HeaderView* header);

    HeaderView* VerticalHeader() const;
    void SetVerticalHeader(HeaderView* header);

    void PaintBegin() override;
    void PaintEnd() override;

    std::u8string_view id() const;
    void set_id(std::u8string_view id);

    TableFlags flags() const;
    void set_flags(TableFlags flags);

    void SetModel(AbstractItemModel* model) override;

    _MW_IMPL
};
}
