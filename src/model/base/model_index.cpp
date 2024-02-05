#include <mvcgui/model/base/model_index.h>
#include <numeric>

namespace mvcgui {
constexpr auto kInvalidValue = std::numeric_limits<size_t>::max();

ModelIndex ModelIndex::kInvalid{ kInvalidValue, kInvalidValue };

ModelIndexRange::ModelIndexRange(const ModelIndex& top_left, const ModelIndex& bottom_right)
	: top_left_{ top_left }, bottom_right_{ bottom_right }
{
	assert(top_left_.valid() && bottom_right_.valid());
	assert(top_left_.row() <= bottom_right_.row());
	assert(top_left_.column() <= bottom_right_.column());
}

void ModelIndexRange::ForeachColumn(size_t row, ForeachCallback&& cb)
{
	for (size_t i = 0; i < column_count(); i++) {
		if (!cb(top_left_ + ModelIndex{row, i}, i))
			break;
	}
}

void ModelIndexRange::ForeachRow(size_t column, ForeachCallback&& cb) {
	for (size_t i = 0; i < row_count(); i++) {
		if (!cb(top_left_ + ModelIndex{i, column}, i))
			break;
	}
}

bool ModelIndex::valid() const {
	return row_ != kInvalidValue && column_ != kInvalidValue;
}

bool operator==(const ModelIndex& x, const ModelIndex& y) {
	return x.row() == y.row() && x.column() == y.column();
}
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y) {
	x.row_ += y.row_;
	x.column_ += y.column_;
	return x;
}
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y) {
	assert(x.row_ >= y.row_);
	assert(x.column_ >= y.column_);
	x.row_ -= y.row_;
	x.column_ -= y.column_;
	return x;
}

ModelIndex operator+(const ModelIndex& x, const ModelIndex& y)
{
	auto tmp = x;
	return tmp += y;
}

ModelIndex operator-(const ModelIndex& x, const ModelIndex& y)
{
	auto tmp = x;
	return tmp -= y;
}
}