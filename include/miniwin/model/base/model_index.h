#pragma once

namespace miniwin {
struct ModelIndex {
    ModelIndex(int row = 0, int column = 0);

    int row;
    int column;

    bool valid() const;
};

bool operator==(const ModelIndex& x, const ModelIndex& y);
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);
ModelIndex operator+(const ModelIndex& x, const ModelIndex& y);
ModelIndex operator-(const ModelIndex& x, const ModelIndex& y);
}
