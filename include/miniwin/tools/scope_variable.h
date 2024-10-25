#pragma once
#include <optional>
#include <cassert>

namespace miniwin {
template <class T>
class ScopeVariable
{
public:
	ScopeVariable() : ScopeVariable(T()) {}
	ScopeVariable(std::convertible_to<T> auto&& init = {});

	/**
	 * 进入作用域
	 *
	 * 如果上一次有set_control, 会在此时应用更改
	 */
	void Enter();
	/**
	 * 退出作用域
	 */
	void Exit() noexcept(std::is_nothrow_copy_assignable_v<T>);
	/**
	 * 模拟发送一次数值改变
	 */
	void SimulateChange();
	/**
	 * 设置控制数值, 会在下一次Enter的时候应用改改
	 */
	template <std::convertible_to<T> E>
	void SetControl(E&& val)
		noexcept(std::is_rvalue_reference_v<decltype(val)>
			         ? true
			         : std::is_nothrow_copy_assignable_v<T>);
	/**
	 * 直接设置数值, 不发送更改通知
	 */
	template <std::convertible_to<T> E>
	void SetValueDirectly(E&& val);
	/**
	 * 数值是否有更改
	 */
	bool HasChange() const { return val_ != end_val_ || simu_change_; }
	/**
	 * 获取上一次退出时的数值
	 */
	decltype(auto) prev_value() const { return end_val_; }
	/**
	 * 是否进入作用域
	 */
	bool entry() const { return entry_; }

	constexpr const T& get() const { return val_; }
	constexpr const T& operator*() const { return get(); }

private:
	// 上一次可能改变的数值
	std::optional<T> control_val_;
	// 这一次进入后的数值
	T val_;
	// 上一次退出时的数值
	T end_val_;
	bool simu_change_;
	bool clear_simu_change_;
	bool entry_;
};

using ScopeCondition = ScopeVariable<bool>;


template <class T>
ScopeVariable<T>::ScopeVariable(std::convertible_to<T> auto&& init)
	: val_(std::forward<decltype(init)>(init)),
	end_val_(std::forward<decltype(init)>(init)),
	simu_change_(false),
	clear_simu_change_(false),
	entry_(false)
{
}

template <class T>
void ScopeVariable<T>::Enter()
{
	assert(!entry_);
	entry_ = true;
	if (control_val_.has_value())
	{
		val_ = std::move(control_val_.value());
		control_val_ = std::nullopt;
	}
	if (simu_change_)
	{
		if (clear_simu_change_)
			simu_change_ = false;
		else
			clear_simu_change_ = true;
	}
}

template <class T>
void ScopeVariable<T>::Exit() noexcept(std::is_nothrow_copy_assignable_v<T>)
{
	end_val_ = val_;
	entry_ = false;
}

template <class T>
void ScopeVariable<T>::SimulateChange()
{
	simu_change_ = true;
	clear_simu_change_ = false;
}

template <class T>
template <std::convertible_to<T> E>
void ScopeVariable<T>::SetControl(
	E&& val) noexcept(std::is_rvalue_reference_v<decltype(val)> ? true : std::is_nothrow_copy_assignable_v<T>)
{
	control_val_ = std::forward<E>(val);
}

template <class T>
template <std::convertible_to<T> E>
void ScopeVariable<T>::SetValueDirectly(E&& val)
{
	val_ = std::forward<E>(val);
}

template <typename T>
bool operator==(const ScopeVariable<T>& x, const ScopeVariable<T>& y)
{
	return x.get() == y.get();
}
}
