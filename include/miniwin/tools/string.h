#pragma once
#include <string>
#include <format>

namespace miniwin {
enum class Encode
{
	kUtf8
};

class String {
public:
	template<class... Args>
	static String Format(const String& fmt, const Args&... args) {
		return std::vformat(fmt.ToStdString(), std::make_format_args(args...)).data();
	}

	String() = default;
	String(const char* str);
	String(const char* str, size_t size);

	String(const String& right) = default;
	String(String&& right) = default;

	String& operator=(const char* right);

	String& operator=(const String& right) = default;
	String& operator=(String&& right) = default;

	String& operator+=(const String& right);

	size_t size() const { return str_.size(); }
	size_t capacity() const { return str_.capacity(); }
	bool empty() const { return str_.empty(); }

	const char* data() const { return str_.data(); }
	char* data() { return str_.data(); }

	void resize(size_t size, const char ch = '\0') { str_.resize(size, ch); }

	const std::string& ToStdString() const;
	std::wstring ToStdWString() const;

private:
	std::string str_;
};

String operator+(const String& x, const String& y);
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