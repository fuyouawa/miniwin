#include <miniwin/tools/regex.h>

#include <regex>

#include <miniwin/tools/list.h>
#include <miniwin/tools/stringlist.h>

namespace miniwin {
class Regex::Impl {
public:
	String pattern_;
};

Regex::Regex(const String& pattern) {
	impl_ = std::make_unique<Impl>();
	impl_->pattern_ = pattern;
}

Regex::~Regex() {}

String Regex::Pattern() const {
	return impl_->pattern_;
}

void Regex::SetPattern(const String& pattern) {
	impl_->pattern_ = pattern;
}

RegexMatch Regex::Match(const String& str) const {
	return {const_cast<Regex*>(this), str};
}

class RegexMatch::Impl {
public:
	Regex* regex_;
	intptr_t position;
	StringList captures;
};

RegexMatch::RegexMatch(Regex* regex, const String& str) {
	impl_ = std::make_unique<Impl>();
	impl_->regex_ = regex;

	std::cmatch m;
	std::regex re(regex->impl_->pattern_.ToStdString());

	if (std::regex_match(str.data(), str.data() + str.size(), m, re)) {
		for (size_t i = 0; i < m.size(); ++i) {
			impl_->captures.EmplaceBack(m.str(i));
		}
	}
}

RegexMatch::~RegexMatch() {}

bool RegexMatch::HasMatch() const {
	return !impl_->captures.empty();
}

String RegexMatch::Captured(size_t index) const {
	return impl_->captures[index];
}
}
