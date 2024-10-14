#pragma once

namespace miniwin {
struct ModelIndex {
    int row = 0;
    int column = 0;

    bool valid() const;
};

bool operator==(const ModelIndex& x, const ModelIndex& y);
ModelIndex& operator+=(ModelIndex& x, const ModelIndex& y);
ModelIndex& operator-=(ModelIndex& x, const ModelIndex& y);
ModelIndex operator+(const ModelIndex& x, const ModelIndex& y);
ModelIndex operator-(const ModelIndex& x, const ModelIndex& y);
}
