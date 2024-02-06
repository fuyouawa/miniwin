#include <mvcgui/tools/algorithm.h>

namespace mvcgui {
int EnableFlags(int src_flags, int flags, bool b) {
    if (b) {
        src_flags |= flags;
    }
    else {
        src_flags &= (~flags);
    }
    return src_flags;
}
}