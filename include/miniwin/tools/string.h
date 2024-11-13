#pragma once
#include <string>
#include <format>

namespace miniwin {
class StringList;

class String {
public:
	static constexpr auto kNPos{ static_cast<size_t>(-1) };

	static String Format(const String& fmt, const auto&... args);

	static String FromUtf16(std::wstring_view wstr);

	String() = default;
	String(const char* str);
	explicit String(const char* str, size_t size);
	explicit String(std::string_view str);
	explicit String(size_t size, char ch);

	String(const String& right) = default;
	String(String&& right) = default;

	String& operator=(const char* right);

	String& operator=(const String& right) = default;
	String& operator=(String&& right) = default;

	String& operator+=(const String& right);
	String& operator+=(char right);

	size_t length() const { return str_.length(); }
	size_t size() const { return str_.size(); }
	size_t capacity() const { return str_.capacity(); }
	bool empty() const { return str_.empty(); }

	const char* data() const { return str_.data(); }
	char* data() { return str_.data(); }

	void resize(size_t size, const char ch = '\0') { str_.resize(size, ch); }

	std::string ToStdString() const;
	std::wstring ToStdWString() const;

	String& Replace(const String& before, const String& after);
	StringList Split(const String& sep) const;
	size_t IndexOf(const String& str, size_t start = 0) const;
	String Substr(size_t begin, size_t end = kNPos) const;

private:
	std::string str_;
};

String String::Format(const String& fmt, const auto&... args) {
	return std::vformat(fmt.ToStdString(), std::make_format_args(args...)).data();
}
String operator+(const String& x, const String& y);
String operator+(const String& x, char y);
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