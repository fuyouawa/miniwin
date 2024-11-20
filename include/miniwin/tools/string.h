#pragma once
#include <string>
#include <format>

namespace miniwin {
class StringList;
class StringConstIterator;
class StringIterator;

class String {
public:
	using iterator = StringIterator;
	using const_iterator = StringConstIterator;
	using value_type = char;
	using pointer = char*;
	using const_pointer = const char*;
	using reference = char&;
	using const_reference = const char&;
	using difference_type = intptr_t;
	using size_type = size_t;

	static constexpr auto kNPos{ static_cast<size_t>(-1) };

	static String Format(const String& fmt, const auto&... args);

	static String FromUtf16(std::wstring_view wstr);
	static String FromNumber(uint64_t num, uint8_t base = 10);

	String() = default;
	String(char ch);
	String(const char* str);
	String(size_t size, char ch);

	explicit String(const char* str, size_t size);
	explicit String(std::string_view str);

	String(const String& right) = default;
	String(String&& right) = default;

	String& operator=(const char* right);

	String& operator=(const String& right) = default;
	String& operator=(String&& right) = default;

	String& operator+=(const String& right);
	String& operator+=(char right);

	String operator+(char right) const;

	size_t length() const { return str_.length(); }
	size_t size() const { return str_.size(); }
	size_t capacity() const { return str_.capacity(); }
	bool empty() const { return str_.empty(); }

	const char* data() const { return str_.data(); }
	char* data() { return str_.data(); }

	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();

	void resize(size_t size, const char ch = '\0') { str_.resize(size, ch); }

	std::string ToStdString() const;
	std::wstring ToStdWString() const;

	uint64_t ToNumber(uint8_t base = 10) const;

	String& Replace(const String& before, const String& after);
	StringList Split(const String& sep) const;
	StringList Split(char sep) const;
	size_t IndexOf(char ch, size_t start = 0) const;
	size_t IndexOf(const String& str, size_t start = 0) const;
	String Substr(size_t begin, size_t end = kNPos) const;

private:
	friend class StringConstIterator;
	friend class StringIterator;

	std::string::const_iterator ToStdIter(const StringConstIterator& iter) const;
	std::string::iterator ToStdIter(const StringIterator& iter);

	const_iterator FromStdIter(const std::string::const_iterator& iter) const;
	iterator FromStdIter(const std::string::iterator& iter);

	std::string str_;
};

class StringConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = String::value_type;
	using size_type = String::size_type;
	using difference_type = String::difference_type;
	using pointer = String::const_pointer;
	using reference = const value_type&;

	StringConstIterator() = default;
	StringConstIterator(size_type index, const String* owner) : owner_(owner), index_(index) {}

	bool IsBegin() const { return index_ == 0; }
	bool IsEnd() const { return index_ == owner_->size(); }

	size_type index() const { return index_; }

	reference operator*() const { return StdIter().operator*(); }
	pointer operator->() const { return StdIter().operator->(); }

	//TODO 边界检查
	StringConstIterator& operator++() { ++index_; return *this; }
	StringConstIterator operator++(int) { auto tmp = *this; ++*this; return tmp; }
	StringConstIterator& operator--() { --index_; return *this; }
	StringConstIterator operator--(int) { auto tmp = *this; --*this; return tmp; }

	StringConstIterator& operator+=(const difference_type off) { index_ += off; return *this; }
	StringConstIterator operator+(const difference_type off) const { auto tmp = *this; tmp += off; return tmp; }
	StringConstIterator& operator-=(const difference_type off) { index_ -= off; return *this; }
	StringConstIterator operator-(const difference_type off) const { auto tmp = *this; tmp -= off; return tmp; }
	difference_type operator-(const StringConstIterator& right) const { return index_ - right.index_; }

	reference operator[](const difference_type off) const { return *(*this + off); }
	bool operator==(const StringConstIterator& right) const {
		return index_ == right.index_ && owner_ == right.owner_;
	}
	bool operator!=(const StringConstIterator& right) const {
		return !operator==(right);
	}

	std::strong_ordering operator<=>(const StringConstIterator& right) const { return index_ <=> right.index_; }

private:
	std::string::const_iterator StdIter() const;

protected:
	const String* owner_ = nullptr;
	size_type index_ = 0;
};

class StringIterator : public StringConstIterator
{
public:
	using Base = StringConstIterator;

	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = String::value_type;
	using size_type = String::size_type;
	using difference_type = String::difference_type;
	using pointer = String::pointer;
	using reference = value_type&;

	StringIterator() = default;
	StringIterator(size_type index, String* owner) : StringConstIterator(index, owner) {}

	reference operator*() const { return const_cast<reference>(Base::operator*()); }
	pointer operator->() const { return const_cast<pointer>(Base::operator->()); }

	StringIterator& operator++() { Base::operator++(); return *this; }
	StringIterator operator++(int) { auto tmp = *this; Base::operator++(); return tmp; }
	StringIterator& operator--() { Base::operator--(); return *this; }
	StringIterator operator--(int) { auto tmp = *this; Base::operator--(); return tmp; }

	StringIterator& operator+=(const difference_type off) { Base::operator+=(off); return *this; }
	StringIterator operator+(const difference_type off) { auto tmp = *this; tmp += off; return tmp; }
	StringIterator& operator-=(const difference_type off) { Base::operator-=(off); return *this; }
	StringIterator operator-(const difference_type off) { auto tmp = *this; tmp -= off; return tmp; }
	using Base::operator--;

	reference operator[](const difference_type off) const { return const_cast<reference>(Base::operator[](off)); }

private:
	std::string::iterator StdIter();
};

bool IsNumber(char ch, uint8_t base = 10);
bool IsNumber(wchar_t ch, uint8_t base = 10);


String String::Format(const String& fmt, const auto&... args) {
	return std::vformat(fmt.ToStdString(), std::make_format_args(args...)).data();
}

String operator+(const String& x, const String& y);
String operator+(char x, const String& y);
}

template<> struct std::formatter<miniwin::String> {
	std::formatter<std::string> fmt;

	constexpr auto parse(std::format_parse_context& ctx) {
		return fmt.parse(ctx);
	}

	auto format(const miniwin::String& str, std::format_context& ctx) const {
		return fmt.format(str.ToStdString(), ctx);
	}
};