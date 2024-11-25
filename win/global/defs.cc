#include <miniwin/global/defs.h>

namespace miniwin {
Alignment operator|(Alignment x, Alignment y) {
	return static_cast<Alignment>(static_cast<size_t>(x) | static_cast<size_t>(y));
}

inline Alignment operator&(Alignment x, Alignment y) {
	return static_cast<Alignment>(static_cast<size_t>(x) & static_cast<size_t>(y));
}
}