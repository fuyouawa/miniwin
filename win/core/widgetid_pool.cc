#include <miniwin/core/widgetid_pool.h>

#include "win/tools/debug.h"

namespace miniwin {
WidgetIdPool& WidgetIdPool::Instance() {
	static WidgetIdPool inst;
	return inst;
}

WidgetId WidgetIdPool::AllocId() {
	MW_ASSERT_X(cur_max_id_ < std::numeric_limits<WidgetId>::max());
	if (id_pool_seek_ > 0) {
		return id_pool_[--id_pool_seek_];
	}
	return cur_max_id_++;
}

bool WidgetIdPool::RecycleId(WidgetId id) {
	MW_ASSERT_X(id != 0);
	if (id_pool_seek_ < sizeof(id_pool_) / sizeof(WidgetId)) {
		id_pool_[id_pool_seek_++] = id;
		return true;
	}
	return false;
}
}
