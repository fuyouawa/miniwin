#pragma once
#include <miniwin/widgets/base/abstract_item_view.h>
#include <miniwin/widgets/view/headerview.h>


namespace miniwin {
class TableView : public AbstractItemView
{
public:
    TableView(Widget* parent);
    ~TableView() override;

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
