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
	String() = default;
	String(const char8_t* str);
	String(std::u8string_view str);

	String(const String& right) = default;
	String(String&& right) = default;

	String& operator=(const char8_t* right);
	String& operator=(std::u8string_view right);

	String& operator=(const String& right) = default;
	String& operator=(String&& right) = default;

	size_t size() const { return str_.size(); }
	size_t capacity() const { return str_.capacity(); }
	bool empty() const { return str_.empty(); }

	const char8_t* data() const { return str_.data(); }
	char8_t* data() { return str_.data(); }

	const char* cdata() const { return reinterpret_cast<const char*>(str_.data()); }
	char* cdata() { return reinterpret_cast<char*>(str_.data()); }
	void resize(size_t size, const char8_t ch = '\0') { str_.resize(size, ch); }

	std::string ToStdString() const;
	std::wstring ToStdWString() const;

private:
	std::u8string str_;
};
}
