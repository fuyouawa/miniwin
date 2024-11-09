#include <miniwin/model/base/model_index.h>

#include "win/tools/debug.h"

namespace miniwin {
bool ModelIndex::valid() const
{
    return row_ != static_cast<size_t>(-1) && column_ != static_cast<size_t>(-1);
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
    MW_ASSERT_X(x.row_ >= y.row_);
    MW_ASSERT_X(x.column_ >= y.column_);
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
