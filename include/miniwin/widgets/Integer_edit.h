#pragma once
#include <miniwin/widgets/text_edit.h>

namespace miniwin {
//TODO 有符号数的处理
class IntegerEdit : public TextEdit {
	MW_OBJECT
public:
	IntegerEdit();
	~IntegerEdit() override;

	/**
	 * 进制
	 */
	uint8_t Base() const;
	/**
	 * 设置进制
	 * @param base 
	 */
	void SetBase(uint8_t base);

	/**
	 * 将输入文本值转为数字（无符号）
	 */
	uint64_t ToUInteger() const;
	/**
	 * 设置数字，内部会根据进制自动转换为对应的文本（无符号）
	 * @param val 
	 */
	void SetUInteger(uint64_t val);

	/**
	 * 是否启动了数值限制
	 */
	bool HasLimit() const;
	/**
	 * 启动数值限制
	 * @param b 
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void EnableLimit(bool b, bool auto_adjust = true);
	/**
	 * 最大数值（无符号）
	 */
	uint64_t MaxUInteger();
	/**
	 * 设置最大数值（无符号）
	 * @param num 
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void SetMaxUInteger(uint64_t num, bool auto_adjust = true);
	/**
	 * 最小数值（无符号）
	 */
	uint64_t MinUInteger() const;
	/**
	 * 设置最小数值（无符号）
	 * @param num
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void SetMinUInteger(uint64_t num, bool auto_adjust = true);

	/**
	 * 调整数值，如果启动了NumberLimit，则确保在MaxNumber范围内
	 */
	void AdjustInteger();

protected:
	void Start() override;
	void PaintBegin(size_t index) override;

	bool FilterInput(FilterInputArgs& args) override;

	_MW_IMPL
};
}
