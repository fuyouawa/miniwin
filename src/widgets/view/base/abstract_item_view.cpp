#include <mvcgui/widgets/view/base/abstract_item_view.h>
#include <mvcgui/model/base/abstract_item_model.h>
#include <mvcgui/delegate/base/abstract_item_delegate.h>
#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
AbstractItemView::AbstractItemView(Widget* const parent, std::u8string_view label, bool show)
	: AbstractMinimumControl{ parent, label, show },
	cur_idx_{ ModelIndex::kInvalid },
	prev_idx_{ ModelIndex::kInvalid }
{
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
	ClearSelection();
	set_selection(idx, true);
}

void AbstractItemView::set_selection(const ModelIndex& idx, bool b) {
	model_->set_selection(idx, b);
	if (b) {
		cur_idx_ = idx;
	}
	else {
		if (idx == cur_idx_) {
			cur_idx_ = ModelIndex::kInvalid;
		}
	}
}

void AbstractItemView::ClearSelection() {
	model_->ClearSelection();
}

bool AbstractItemView::is_selected_item(const ModelIndex& idx) const {
	return model_->is_selected(idx);
}

void AbstractItemView::OnUpdate() {
	AbstractMinimumControl::OnUpdate();
	if (cur_idx_ != prev_idx_) {
		Emit(on_current_changed_, cur_idx_, prev_idx_);
	}
	prev_idx_ = cur_idx_;
}
}