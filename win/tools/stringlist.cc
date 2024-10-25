#include <miniwin/tools/stringlist.h>

namespace miniwin {
StringList::StringList(std::initializer_list<String> args)
    : List(args)
{
}
}
