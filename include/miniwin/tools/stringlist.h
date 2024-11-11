#pragma once
#include <miniwin/tools/string.h>
#include <miniwin/tools/list.h>

namespace miniwin {
class StringList : public List<String>
{
public:
	StringList() = default;
	StringList(std::initializer_list<String> args);
};
}