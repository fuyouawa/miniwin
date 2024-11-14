#include <miniwin/tools/list.h>

#include "win/tools/debug.h"

namespace miniwin {
namespace internal {
void VerifyIndex(size_t index, size_t size) {
	MW_ASSERT_X(index < size);
}

void VerifyIndex(size_t index, intptr_t off, size_t size) {
	if (off < 0)
		MW_ASSERT_X(index >= static_cast<size_t>(-off));
	VerifyIndex(index + off, size);
}

void VerifyDiff(intptr_t diff) {
	MW_ASSERT_X(diff >= 0);
}

void VerifyAddIndex(size_t index, intptr_t off, size_t size) {
	MW_ASSERT_X(index + off <= size);
}

void VerifySubIndex(size_t index, intptr_t off, size_t size) {
	MW_ASSERT_X(index <= size
		&& static_cast<intptr_t>(index) >= off
		&& static_cast<intptr_t>(index) - off >= 0);
}
}
}
