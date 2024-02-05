#include <mvcgui/widgets/view/base/abstract_item_view.h>
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/widgets/delegate/base/abstract_item_delegate.h>
#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
AbstractItemView::AbstractItemView(
	Widget* const parent,
	std::u8string_view label,
	AbstractItemModelPtr default_model,
	AbstractItemDelegatePtr default_delegate,
	bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_idx_{ ModelIndex::kInvalid },
	prev_idx_{ ModelIndex::kInvalid }
{
	set_model(default_model);
	set_delegate(default_delegate);
}

void AbstractItemView::set_delegate(AbstractItemDelegatePtr delegate)
{
	if (delegate_) {
		DisConnect(delegate_->on_current_index_changed_);
		DisConnect(delegate_->on_selection_changed_);
	}
	delegate_ = delegate;

	Connect(delegate_->on_current_index_changed_, [this](auto idx) {
		set_current_index(idx);
		});
	Connect(delegate_->on_selection_changed_, [this](auto idx, bool is_selected) {
		set_selection(idx, is_selected);
		});
}

void AbstractItemView::set_current_index(const ModelIndex& idx) {
	clear_selections();
	set_selection(idx, true);
}

void AbstractItemView::set_selection(const ModelIndex& idx, bool b) {
	if (b) {
		selection_items_.push_back(idx);
		cur_idx_ = idx;
	}
	else {
		std::erase(selection_items_, idx);
		if (idx == cur_idx_) {
			cur_idx_ = ModelIndex::kInvalid;
		}
	}
}

void AbstractItemView::clear_selections() {
	selection_items_.clear();
	cur_idx_ = ModelIndex::kInvalid;
}

bool AbstractItemView::is_selected_item(const ModelIndex& idx) const {
	return IsContainer(selection_items_, idx);
}

void AbstractItemView::PaintItems() {
	for (size_t i = 0; i < model()->row_count(); i++) {
		for (size_t j = 0; j < model()->column_count(); j++) {
			delegate()->Paint(*this, { i, j });
		}
	}
}

void AbstractItemView::OnUpdate() {
	AbstractMinimumControl::OnUpdate();
	if (cur_idx_ != prev_idx_) {
		Emit(on_current_changed_, cur_idx_, prev_idx_);
	}
	prev_idx_ = cur_idx_;
}
}