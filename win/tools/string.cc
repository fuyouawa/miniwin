#include <miniwin/tools/string.h>

#include <Windows.h>

#include <sstream>
#include <bitset>

#include <miniwin/tools/stringlist.h>
#include "debug.h"

namespace miniwin {
String String::FromUtf16(std::wstring_view wstr) {
	int conv_size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
	String str(conv_size, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, str.data(), conv_size, nullptr, nullptr);
	return str;
}

String String::FromInteger(uint64_t num, uint8_t base) {
	if (!(base == 2 || base == 8 || base == 10 || base == 16)) {
		MW_THROW_EX(std::invalid_argument, "Illegal 'base' = {}, must be 2 or 8 or 10 or 16", base);
	}

	if (base == 2)
		return String(std::bitset<std::numeric_limits<uint64_t>::digits>(num).to_string());
	if (base == 10)
		return String(std::to_string(num));

	std::ostringstream oss;
	if (base == 8)
		oss << std::oct;
	else
		oss << std::hex;
	oss << num;
	return String(oss.str());
}

String::String(char ch) : str_(1, ch) {}

String::String(const char* str)
	: str_(str) {}

String::String(const char* str, size_t size) : str_(str, size) {}

String::String(std::string_view str)
	: str_(str) {}

String::String(size_t size, char ch) : str_(size, ch) {}

String& String::operator=(const char* right) {
	str_ = right;
	return *this;
}

String& String::operator+=(const String& right) {
	str_ += right.str_;
	return *this;
}

String& String::operator+=(char right) {
	str_ += right;
	return *this;
}

String String::operator+(char right) const {
	String x1(*this);
	return x1 += right;
}

String::const_iterator String::begin() const {
	return FromStdIter(str_.begin());
}

String::iterator String::begin() {
	return FromStdIter(str_.begin());
}

String::const_iterator String::end() const {
	return FromStdIter(str_.end());
}

String::iterator String::end() {
	return FromStdIter(str_.end());
}

std::string String::ToStdString() const {
	return str_;
}

std::wstring String::ToStdWString() const {
	auto conv_size = MultiByteToWideChar(CP_UTF8, 0, data(), size(), nullptr, 0);
	std::wstring wstr(conv_size, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, data(), size(), wstr.data(), conv_size);
	return wstr;
}

uint64_t String::ToInteger(uint8_t base) const {
	return std::stoull(str_, nullptr, base);
}

String& String::Replace(const String& before, const String& after) {
	size_t start = 0;
	while ((start = IndexOf(before, start)) != kNPos) {
		str_.replace(start, before.size(), after.str_);
		start += after.size();
	}
	return *this;
}

StringList String::Split(const String& sep) const {
	StringList total;
	size_t start = 0;
	size_t end = IndexOf(sep);
	while (end != kNPos) {
		total.PushBack(Substr(start, end));
		start = end + sep.size();
		end = IndexOf(sep, start);
	}
	total.PushBack(Substr(start));
	return total;
}

StringList String::Split(char sep) const {
	StringList total;
	size_t start = 0;
	size_t end = IndexOf(sep);
	while (end != kNPos) {
		total.PushBack(Substr(start, end));
		start = end + 1;
		end = IndexOf(sep, start);
	}
	total.PushBack(Substr(start));
	return total;
}

size_t String::IndexOf(char ch, size_t start) const {
	return str_.find(ch, start);
}

size_t String::IndexOf(const String& str, size_t start) const {
	return str_.find(str.str_, start);
}

String String::Substr(size_t begin, size_t end) const {
	return String(str_.substr(begin, end - begin));
}

std::string::const_iterator String::ToStdIter(const StringConstIterator& iter) const {
	return str_.begin() + iter.index();
}

std::string::iterator String::ToStdIter(const StringIterator& iter) {
	return str_.begin() + iter.index();
}

String::const_iterator String::FromStdIter(const std::string::const_iterator& iter) const {
	auto diff = iter - str_.begin();
	MW_ASSERT_X(diff >= 0);
	return { static_cast<size_type>(diff), this };
}

String::iterator String::FromStdIter(const std::string::iterator& iter) {
	auto diff = iter - str_.begin();
	MW_ASSERT_X(diff >= 0);
	return { static_cast<size_type>(diff), this };
}

std::string::const_iterator StringConstIterator::StdIter() const {
	return owner_->ToStdIter(*this);
}

std::string::iterator StringIterator::StdIter() {
	return const_cast<String*>(this->owner_)->ToStdIter(*this);
}

bool IsNumber(char ch, uint8_t base) {
	MW_ASSERT_X(base == 2 || base == 8 || base == 10 || base == 16);
	if (base != 16) {
		return (ch - '0') < base;
	}
	return (ch >= '0' && ch <= '9') ||
		(ch >= 'A' && ch <= 'F') ||
		(ch >= 'a' && ch <= 'f');
}

bool IsNumber(wchar_t ch, uint8_t base) {
	if (ch > (std::numeric_limits<char>::max)()) {
		return false;
	}
	return IsNumber(static_cast<char>(ch), base);
}

String operator+(const String& x, const String& y) {
	String x1(x);
	return x1 += y;
}

String operator+(char x, const String& y) {
	String x1(x);
	return x1 += y;
}
}
