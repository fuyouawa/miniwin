#pragma once
#include <miniwin/model/base/abstract_item_model.h>
#include <miniwin/tools/stringlist.h>

namespace miniwin {
class StandardItemModel : public AbstractItemModel
{
public:
    StandardItemModel(Object* parent);
    ~StandardItemModel() override;

    void InsertRows(size_t row, size_t count) override;
    void RemoveRows(size_t row, size_t count) override;
    size_t RowCount() const override;

    void InsertColumns(size_t column, size_t count) override;
    void RemoveColumns(size_t column, size_t count) override;
    size_t ColumnCount() const override;

    Variant Data(const ModelIndex& index, ItemRole role) const override;
    void SetData(const ModelIndex& index, const Variant& data, ItemRole role) override;

    Variant HeaderData(size_t section, HeaderOrientation orientation, ItemRole role) const override;
    void SetHeaderData(size_t section, HeaderOrientation orientation, const Variant& data, ItemRole role) override;

    String Text(const ModelIndex& index) const;
    void SetText(const ModelIndex& index, const String& text);

    void SetRowTexts(size_t row, size_t begin_column, const StringList& texts);
    void SetColumnTexts(size_t begin_row, size_t column, const StringList& texts);

    int Flags(const ModelIndex& index) const;
    void SetFlags(const ModelIndex& index, int flags);

    String HeaderText(int section, HeaderOrientation orientation) const;
    void SetHeaderText(int section, HeaderOrientation orientation, const String& text);

    void SetHorizontalHeaderTexts(const StringList& texts);
    void SetVerticalHeaderTexts(const StringList& texts);

    int HeaderFlags(int section, HeaderOrientation orientation) const;
    void SetHeaderFlags(int section, HeaderOrientation orientation, int flags);

    void Clear() override;

    _MW_IMPL
};
}
