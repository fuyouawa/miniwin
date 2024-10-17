#pragma once
namespace miniwin {
class ModelIndex {
public:
    ModelIndex(size_t row = 0, size_t column = 0) : row_(row), column_(column) {}

    bool valid() const;

    size_t row() const { return row_; }
    void set_row(size_t row) { row_ = row; }

    size_t column() const { return column_; }
    void set_column(size_t column) { column_ = column; }

private:
    friend ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
    friend ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);

    size_t row_;
    size_t column_;
};

bool operator==(const ModelIndex& x, const ModelIndex& y);
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);
ModelIndex operator+(const ModelIndex& x, const ModelIndex& y);
ModelIndex operator-(const ModelIndex& x, const ModelIndex& y);
}
