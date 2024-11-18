#include "table_view_impl.h"

#include <miniwin/core/imgui.h>
#include <miniwin/delegate/base/abstract_item_delegate.h>

namespace miniwin {
TableView::TableView() {
	impl_ = std::make_unique<Impl>(this);
}

TableView::~TableView() {}

SharedHeaderView TableView::HorizontalHeader() const {
	return impl_->Header(HeaderOrientation::Horizontal);
}

void TableView::SetHorizontalHeader(const SharedHeaderView& header) {
	impl_->SetHeader(HeaderOrientation::Horizontal, header);
}

SharedHeaderView TableView::VerticalHeader() const {
	return impl_->Header(HeaderOrientation::Vertical);
}

void TableView::SetVerticalHeader(const SharedHeaderView& header) {
	impl_->SetHeader(HeaderOrientation::Vertical, header);
}

void TableView::PaintBegin() {
	AbstractItemView::PaintBegin();
	auto m = Model();
	auto col_count = m->ColumnCount();
	auto row_count = m->RowCount();

	if (imgui::BeginTable(Name(), col_count, 0, Size())) {
		auto hori = HorizontalHeader();
		if (hori && hori->Visible()) {
			for (size_t col = 0; col < col_count; ++col) {
				auto text = m->HeaderData(col, HeaderOrientation::Horizontal, ItemRole::Display).ToString();
				auto flags = m->HeaderData(col, HeaderOrientation::Horizontal, ItemRole::Flags).ToInt32();
				imgui::TableSetupColumn(text, flags);
			}
			imgui::TableNextRow(imgui::kTableRowHeaders);

			for (size_t col = 0; col < col_count; ++col) {
				imgui::TableSetColumnIndex(col);
				hori->PaintSection(col);
			}
		}

		auto vert = VerticalHeader();
		bool show_vert = vert && vert->Visible();
		if (show_vert)
			--col_count;

		auto d = ItemDelegate();
		auto self = shared_from_this();

		for (size_t row = 0; row < row_count; ++row) {
			imgui::TableNextRow();
			if (show_vert) {
				vert->PaintSection(row);
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

void TableView::SetModel(const SharedItemModel& model) {
	AbstractItemView::SetModel(model);
	for (auto& header : impl_->headers_) {
		auto h = header.second;
		if (h) {
			auto m = h->Model();
			if (!m || m == Model()) {
				h->SetModel(model);
			}
		}
	}
}

void TableView::Initialize(const SharedObject& parent) {
	AbstractItemView::Initialize(parent);
	impl_->Init();
}
}
