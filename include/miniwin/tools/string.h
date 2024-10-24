#pragma once
#include <string>
#include <format>

#include <miniwin/tools/list.h>

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

	String& operator=(const char8_t* other);
	String& operator=(std::u8string_view other);

	size_t size() const { return str_.size(); }
	size_t count() const { return str_.size(); }
	size_t length() const { return str_.size(); }
	size_t capacity() const { return str_.capacity(); }

	const char8_t* data() const { return str_.data(); }
	char8_t* data() { return str_.data(); }

	const char* cdata() const { return reinterpret_cast<const char*>(str_.data()); }
	char* cdata() { return reinterpret_cast<char*>(str_.data()); }
	void resize(size_t size, const char8_t ch = '\0') { str_.resize(size, ch); }

	bool IsEmpty() const { return str_.empty(); }

	std::string ToStdString() const;
	std::wstring ToStdWString() const;

private:
	std::u8string str_;
};


class StringList : public List<String>
{
public:
	using Inherit = List<String>;

	StringList(std::initializer_list<String> args);
};
}
