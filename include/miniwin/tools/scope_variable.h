#pragma once
#include <optional>
#include <cassert>

namespace miniwin
{
	template <class T>
	class ScopeVariable
	{
	public:
		ScopeVariable() : ScopeVariable(T{})
		{
		}

		template <std::convertible_to<T> E>
		ScopeVariable(E&& init)
			: val_{init},
			  end_val_{init},
			  simu_change_{false},
			  clear_simu_change_{false},
			  entry_{false}
		{
		}

		/**
		 * ����������
		 *
		 * �����һ����set_control, ���ڴ�ʱӦ�ø���
		 */
		void Enter()
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

		/**
		 * �˳�������
		 */
		void Exit() noexcept(std::is_nothrow_copy_assignable_v<T>)
		{
			end_val_ = val_;
			entry_ = false;
		}

		/**
		 * ģ�ⷢ��һ����ֵ�ı�
		 */
		void SimulateChange()
		{
			simu_change_ = true;
			clear_simu_change_ = false;
		}

		/**
		 * ���ÿ�����ֵ, ������һ��Enter��ʱ��Ӧ�øĸ�
		 * @param val Ҫ���õ���ֵ
		 */
		template <std::convertible_to<T> E>
		void SetControl(E&& val)
			noexcept(std::is_rvalue_reference_v<decltype(val)>
				         ? true
				         : std::is_nothrow_copy_assignable_v<T>)
		{
			control_val_ = std::forward<E>(val);
		}

		template <std::convertible_to<T> E>
		void SetValueDirectly(E&& val)
		{
			val_ = std::forward<E>(val);
		}

		/**
		 * ��ֵ�Ƿ��и���
		 */
		bool HasChange() const { return val_ != end_val_ || simu_change_; }

		/**
		 * ��ȡ��һ���˳�ʱ����ֵ
		 */
		decltype(auto) prev_value() const { return end_val_; }

		/**
		 * �Ƿ����������
		 */
		bool entry() const { return entry_; }

		constexpr const T& get() const { return val_; }
		constexpr const T& operator*() const { return get(); }

	private:
		// ��һ�ο��ܸı����ֵ
		std::optional<T> control_val_;
		// ��һ�ν�������ֵ
		T val_;
		// ��һ���˳�ʱ����ֵ
		T end_val_;
		bool simu_change_;
		bool clear_simu_change_;
		bool entry_;
	};

	template <typename T>
	bool operator==(const ScopeVariable<T>& x, const ScopeVariable<T>& y)
	{
		return x.get() == y.get();
	}

	using ScopeCondition = ScopeVariable<bool>;
}
