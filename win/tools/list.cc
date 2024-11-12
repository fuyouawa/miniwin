#include <miniwin/tools/list.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace internal {
void VerifyIndex(size_t index, size_t size) {
	MW_ASSERT_X(index < size);
}
void VerifyDiff(intptr_t diff) {
	MW_ASSERT_X(diff >= 0);
}
}
}