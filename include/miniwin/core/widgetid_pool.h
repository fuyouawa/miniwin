#pragma once
#include <miniwin/defs.h>
#include <cstdint>

namespace miniwin {
class WidgetIdPool {
public:
    static WidgetIdPool& Instance();

    WidgetId AllocId();
    bool RecycleId(WidgetId id);

private:
    WidgetIdPool() = default;

    WidgetId cur_max_id_ = 1;
    uint8_t id_pool_seek_ = 0;
    WidgetId id_pool_[128];
};
}