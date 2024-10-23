#include <miniwin/tools/variant.h>

#include <cassert>

namespace miniwin {
namespace {
char* CopyStr(const char* str, size_t size)
{
	auto t = new char[size];
	std::copy_n(str, size, t);
	return t;
}
char8_t* CopyU8Str(const char8_t* str, size_t size)
{
	return reinterpret_cast<char8_t*>(CopyStr(reinterpret_cast<const char*>(str), size));
}

template<class T, class... Ts>
T Convert(const std::variant<Ts...>& v, VariantType type, bool* ok = nullptr)
{
	bool suc = v.index() == static_cast<size_t>(type);
	if (ok)
		*ok = suc;
	if (suc)
		return std::get<T>(v);
	return {};
}
}

Variant::Variant() = default;


Variant::Variant(const Variant& other)
{
	switch (other.Type())
	{
	case VariantType::kString:
	{
		auto s = Convert<char*>(other.var_, VariantType::kString);
		assert(s);
		var_ = CopyStr(s, strlen(s) + 1);
		break;
	}
	case VariantType::kUtf8String:
	{
		auto s = Convert<char8_t*>(other.var_, VariantType::kUtf8String);
		assert(s);
		var_ = CopyU8Str(s, strlen(reinterpret_cast<char*>(s)) + 1);
		break;
	}
	default:
		var_ = other.var_;
		break;
	}
}

Variant& Variant::operator=(const Variant& other)
{
	auto tmp = Variant(other);
	var_.swap(tmp.var_);
	return *this;
}

Variant::Variant(std::nullptr_t)
	: var_(nullptr)
{
}

Variant::Variant(std::string_view str)
{
	var_ = CopyStr(str.data(), str.size() + 1);
}

Variant::Variant(std::u8string_view str)
{
	var_ = CopyU8Str(str.data(), str.size() + 1);
}

Variant::Variant(int32_t i32)
{
	var_ = i32;
}

Variant::Variant(uint32_t u32)
{
	var_ = u32;
}

Variant::Variant(int64_t i64)
{
	var_ = i64;
}

Variant::Variant(uint64_t u64)
{
	var_ = u64;
}

Variant::Variant(float f)
{
	var_ = f;
}

Variant::Variant(double d)
{
	var_ = d;
}

Variant::Variant(char c)
{
	var_ = c;
}

Variant::Variant(bool b)
{
	var_ = b;
}

Variant::~Variant()
{
	switch (Type())
	{
	case VariantType::kString:
		delete[] std::get<char*>(var_);
		break;
	case VariantType::kUtf8String:
		delete[] std::get<char8_t*>(var_);
		break;
	default:
		break;
	}
}

VariantType Variant::Type() const
{
	return static_cast<VariantType>(var_.index());
}

bool Variant::IsNull() const
{
	return std::holds_alternative<std::nullptr_t>(var_);
}

bool Variant::IsEmpty() const
{
	return std::holds_alternative<std::monostate>(var_);
}

bool Variant::IsFloatingPoint() const
{
	auto t = Type();
	return t == VariantType::kFloat || t == VariantType::kDouble;
}

bool Variant::IsInteger() const
{
	auto t = Type();
	return t == VariantType::kInt32 || t == VariantType::kInt64
		|| t == VariantType::kUInt32 || t == VariantType::kUInt64;
}

bool Variant::IsNumber() const
{
	return IsInteger() || IsFloatingPoint();
}

size_t Variant::ToInteger(bool* ok) const
{
	switch (Type())
	{
	case VariantType::kInt32:
		return ToInt32(ok);
	case VariantType::kUInt32:
		return ToUInt32(ok);
	case VariantType::kInt64:
		return ToInt64(ok);
	case VariantType::kUInt64:
		return ToUInt64(ok);
	default:
		if (ok) *ok = false;
		return {};
	}
}

std::string Variant::ToString(bool* ok) const
{
	if (auto s = Convert<char*>(var_, VariantType::kString, ok))
		return s;
	return {};
}

std::u8string Variant::ToUtf8String(bool* ok) const
{
	if (auto s = Convert<char8_t*>(var_, VariantType::kUtf8String, ok))
		return s;
	return {};
}

int32_t Variant::ToInt32(bool* ok) const
{
	return Convert<int32_t>(var_, VariantType::kInt32, ok);
}

int64_t Variant::ToInt64(bool* ok) const
{
	return Convert<int64_t>(var_, VariantType::kInt64, ok);
}

uint32_t Variant::ToUInt32(bool* ok) const
{
	return Convert<uint32_t>(var_, VariantType::kUInt32, ok);
}

uint64_t Variant::ToUInt64(bool* ok) const
{
	return Convert<uint64_t>(var_, VariantType::kUInt64, ok);
}

char Variant::ToChar(bool* ok) const
{
	return Convert<char>(var_, VariantType::kChar, ok);
}

bool Variant::ToBool(bool* ok) const
{
	return Convert<bool>(var_, VariantType::kBool, ok);
}
}
