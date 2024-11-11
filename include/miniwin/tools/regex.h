#pragma once
#include <miniwin/tools/string.h>
#include <miniwin/defs.h>

namespace miniwin {
class RegexMatch;

class Regex {
public:
	Regex() = default;
	Regex(const String& pattern);
	~Regex();

	String Pattern() const;
	void SetPattern(const String& pattern);

	RegexMatch Match(const String& str) const;

private:
	friend class RegexMatch;
	_MW_IMPL
};


class RegexMatch {
public:
	RegexMatch(Regex* regex, const String& str);
	~RegexMatch();

	bool HasMatch() const;
	String Captured(size_t index) const;

	_MW_IMPL
};
}