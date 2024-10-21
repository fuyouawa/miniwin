#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/header_view.h>


namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent, std::u8string_view id = u8"TableView");
    ~TableView() override;

    std::u8string_view id() const;
    void set_id(std::u8string_view id);

    TableFlags flags() const;
    void set_flags(TableFlags flags);


    HeaderView* HorizontalHeader() const;
    void SetHorizontalHeader(HeaderView* header);

    HeaderView* VerticalHeader() const;
    void SetVerticalHeader(HeaderView* header);

    void SetModel(AbstractItemModel* model) override;

protected:
    void PaintBegin() override;

    _MW_IMPL
};
}
