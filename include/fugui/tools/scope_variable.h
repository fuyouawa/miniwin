#pragma once
#include <optional>
#include <concepts>
#include <assert.h>

namespace fugui {
template<std::equality_comparable T>
class ScopeVariable {
public:
	template<std::convertible_to<T> E>
	ScopeVariable(E&& init = E())
		: val_{ init },
		end_val_{ init },
		simu_change_{ false },
		clear_simu_change_{ false },
		entry_{ false }
	{}

	void Entry() {
		assert(!entry_);
		entry_ = true;
		if (control_val_.has_value()) {
			val_ = std::move(control_val_.value());
			control_val_ = std::nullopt;
		}
		if (simu_change_) {
			if (clear_simu_change_)
				simu_change_ = false;
			else
				clear_simu_change_ = true;
		}
	}

	void Exit() noexcept(std::is_nothrow_copy_assignable_v<T>) {
		end_val_ = val_;
		entry_ = false;
	}

	void SimulateChange() { simu_change_ = true; clear_simu_change_ = false; }

	template<std::convertible_to<T> E>
	void set_control(E&& val) noexcept(std::is_rvalue_reference_v<decltype(val)> ? true : std::is_nothrow_copy_assignable_v<T>)
	{ control_val_ = std::forward<T>(val); }

	bool is_changed() const { return val_ != end_val_ || simu_change_; }
	bool entry() const { return entry; }

	constexpr const T& get() const { return val_; }
	constexpr const T& operator*() const { return get(); }

private:
	std::optional<T> control_val_;
	T val_;
	T end_val_;
	bool simu_change_;
	bool clear_simu_change_;
	bool entry_;
};

template<typename T>
bool operator==(const ScopeVariable<T>& x, const ScopeVariable<T>& y) {
	return x.get() == y.get();
}

using ScopeCondition = ScopeVariable<bool>;
}