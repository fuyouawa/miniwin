#pragma once
#include <functional>

namespace mvcgui {
enum class InvokeType {
	kAuto,
	kDirect,
	kQueued
};

enum class ConnectionType {
	kUnique,
	kReplace,
	kSingle
};

class AbstractObject
{
public:
	using Functor = std::function<void()>;

	virtual ~AbstractObject() = default;

	virtual void Invoke(Functor&& func, InvokeType type = InvokeType::kAuto) const = 0;
};
}