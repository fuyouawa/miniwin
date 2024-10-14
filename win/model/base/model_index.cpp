#include <miniwin/model/base/model_index.h>
#include <cassert>

namespace miniwin {
ModelIndex::ModelIndex(int row, int column)
    : row(row),
    column(column)
{
}

bool ModelIndex::valid() const
{
    return row > 0 && column > 0;
}

bool operator==(const ModelIndex& x, const ModelIndex& y) {
    return x.row == y.row && x.column == y.column;
}
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y) {
    x.row += y.row;
    x.column += y.column;
    return x;
}
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y) {
    assert(x.row >= y.row);
    assert(x.column >= y.column);
    x.row -= y.row;
    x.column -= y.column;
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
