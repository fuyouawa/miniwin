#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/view/headerview.h>


namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent, std::u8string_view id = u8"TableView");
    ~TableView() override;

    std::u8string_view Id() const;
    void SetId(std::u8string_view id);

    TableFlags Flags() const;
    void SetFlags(TableFlags flags);

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
