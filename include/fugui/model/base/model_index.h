#pragma once
#include <functional>
#include <assert.h>

namespace fugui {
class ModelIndex;

bool operator==(const ModelIndex& x, const ModelIndex& y);
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);
ModelIndex operator+(const ModelIndex& x, const ModelIndex& y);
ModelIndex operator-(const ModelIndex& x, const ModelIndex& y);

class ModelIndex {
	friend ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
	friend ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);
public:
	static ModelIndex kInvalid;

	ModelIndex(size_t row = 0, size_t col = 0) : row_{ row }, column_{ col } {}

	bool valid() const;
	auto row() const { return row_; }
	auto column() const { return column_; }

	void set_row(size_t row) { row_ = row; }
	void set_column(size_t col) { column_ = col; }

private:
	size_t row_;
	size_t column_;
};

class ModelIndexRange
{
public:
	ModelIndexRange() = default;
	ModelIndexRange(const ModelIndex& top_left, const ModelIndex& bottom_right);
	using ForeachCallback = std::function<bool(const ModelIndex& idx, size_t i)>;

	auto& top_left() const { return top_left_; }
	auto& bottom_right() const { return bottom_right_; }
	auto row_count() const { return bottom_right_.row() - top_left_.row(); }
	auto column_count() const { return bottom_right_.column() - top_left_.column(); }

	void ForeachColumn(size_t row, ForeachCallback&& cb);
	void ForeachRow(size_t column, ForeachCallback&& cb);

private:
	ModelIndex top_left_;
	ModelIndex bottom_right_;
};
}