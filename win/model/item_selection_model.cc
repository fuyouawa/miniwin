#include <win/model/item_selection_model_impl.h>

#include "win/tools/debug.h"

namespace miniwin {
bool ItemSelection::valid() const {
	return top_left_.valid() && bottom_right_.valid()
		&& top_left_.row() <= bottom_right_.row()
		&& top_left_.column() <= bottom_right_.column();
}

bool operator==(const ItemSelection& x, const ItemSelection& y) {
	return x.top_left() == y.top_left() && x.bottom_right() == y.bottom_right();
}

ItemSelectionModel::ItemSelectionModel() {
	impl_ = std::make_unique<Impl>(this);
}

ItemSelectionModel::~ItemSelectionModel() {}

const ItemSelection& ItemSelectionModel::CurrentSelection() const {
	return impl_->current_selection_;
}

const SharedItemModel& ItemSelectionModel::Model() const {
	return impl_->model_;
}

void ItemSelectionModel::SetModel(const SharedItemModel& model) {
	if (impl_->model_ == model)
		return;
	impl_->model_ = model;
	impl_->current_selection_ = {};
	impl_->selections_.clear();
}

void ItemSelectionModel::Select(size_t row, size_t column, ItemSelectionType selection_type) {
	Select({{row, column}}, selection_type);
}

void ItemSelectionModel::Select(const ItemSelection& selection, ItemSelectionType selection_type) {
	MW_ASSERT_X(selection.valid());
	if (selection_type == ItemSelectionType::ClearSelect) {
		impl_->Clear();
		selection_type = ItemSelectionType::Select;
	}
	impl_->Select(selection, selection_type == ItemSelectionType::Select);
	OnSelectionChanged(selection, selection_type);
}

void ItemSelectionModel::Clear() {
	impl_->Clear();
	OnClearedSelection();
}

bool ItemSelectionModel::IsSelected(const ModelIndex& index) const {
	MW_ASSERT_X(index.valid());
	return impl_->Contains(index);
}
}
