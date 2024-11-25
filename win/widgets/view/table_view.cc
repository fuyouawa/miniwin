#include <miniwin/widgets/view/table_view.h>

#include <miniwin/core/imgui.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>
#include <miniwin/delegate/selectable_item_delegate.h>
#include <miniwin/tools/scope_variable.h>
#include <miniwin/model/item_selection_model.h>
#include <miniwin/delegate/table_header_item_delegate.h>

namespace miniwin {
class TableView::Impl {
public:
	Impl(TableView* owner) : owner_(owner) {}

	void Awake() {
		auto self = owner_->shared_from_this();

		auto d = Create<SelectableItemDelegate>(self);
		owner_->SetItemDelegate(d);

		auto d2 = Create<TableHeaderItemDelegate>(self);
		d2->SetOrientation(HeaderOrientation::kHorizontal);
		owner_->SetHeaderItemDelegate(HeaderOrientation::kHorizontal, d2);

		auto s = Create<ItemSelectionModel>(self);
		s->SetModel(owner_->Model());
		owner_->SetSelectionModel(s);
	}

	TableView* owner_;
	ScopeVariable<Vector2D> position_sc_;
	bool headers_visible_[2]{true, true};
	SharedItemDelegate headers_delegate_[2];
	Vector2D size_to_set_;
	Vector2D really_size_;
};

TableView::TableView() {
	impl_ = std::make_unique<Impl>(this);
}

TableView::~TableView() {}

void TableView::SetHeaderVisible(HeaderOrientation orientation, bool b) {
	impl_->headers_visible_[static_cast<size_t>(orientation)] = b;
}

bool TableView::IsHeaderVisible(HeaderOrientation orientation) const {
	return impl_->headers_visible_[static_cast<size_t>(orientation)]
		&& HeaderItemDelegate(orientation) != nullptr;
}

void TableView::SetHeaderItemDelegate(HeaderOrientation orientation, const SharedItemDelegate& item_delegate) {
	impl_->headers_delegate_[static_cast<size_t>(orientation)] = item_delegate;
}

const SharedItemDelegate& TableView::HeaderItemDelegate(HeaderOrientation orientation) const {
	return impl_->headers_delegate_[static_cast<size_t>(orientation)];
}

void TableView::PaintBegin(size_t index) {
	AbstractItemView::PaintBegin(index);
	auto m = Model();
	auto self = shared_from_this();
	auto col_count = m->ColumnCount();
	auto row_count = m->RowCount();

	if (imgui::BeginTable(Name(), col_count, 0, impl_->size_to_set_)) {
		auto cur_size = imgui::GetItemRectSize();
		if (cur_size != impl_->really_size_) {
			if (IsUpdated()) {
				OnSizeChanged(cur_size, impl_->really_size_);
			}
			impl_->really_size_ = cur_size;
		}

		if (IsHeaderVisible(HeaderOrientation::kHorizontal)) {
			for (size_t col = 0; col < col_count; ++col) {
				auto text = m->HeaderData(col, HeaderOrientation::kHorizontal, ItemRole::kDisplay).ToString();
				auto flags = m->HeaderData(col, HeaderOrientation::kHorizontal, ItemRole::kFlags).ToInt32();
				imgui::TableSetupColumn(text, flags);
			}
			imgui::TableNextRow(imgui::kTableRowHeaders);

			auto hd = HeaderItemDelegate(HeaderOrientation::kHorizontal);
			for (size_t col = 0; col < col_count; ++col) {
				imgui::TableSetColumnIndex(col);
				hd->Paint(self, { 0, col });
			}
		}

		bool show_vert = IsHeaderVisible(HeaderOrientation::kVertical);
		if (show_vert)
			--col_count;

		auto d = ItemDelegate();
		auto vd = HeaderItemDelegate(HeaderOrientation::kVertical);

		for (size_t row = 0; row < row_count; ++row) {
			imgui::TableNextRow();
			if (show_vert) {
				vd->Paint(self, { row, 0 });
			}
			if (d) {
				for (size_t col = 0; col < col_count; ++col) {
					imgui::TableSetColumnIndex(col);
					d->Paint(self, {row, col});
				}
			}
		}

		imgui::EndTable();
	}
}

Vector2D TableView::Size() const {
	return impl_->really_size_ == Vector2D::kZero
		       ? impl_->size_to_set_
		       : impl_->really_size_;
}

void TableView::SetSize(const Vector2D& size) {
	impl_->size_to_set_ = size;
}

void TableView::Awake() {
	AbstractItemView::Awake();
	impl_->Awake();
}
}
