#pragma once
#include <miniwin/widgets/text_edit.h>

namespace miniwin {
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
	 * 将输入文本值转为数字
	 */
	uint64_t ToInteger() const;
	/**
	 * 设置数字，内部会根据进制自动转换为对应的文本
	 * @param val 
	 */
	void SetInteger(uint64_t val);

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
	 * 最大数值
	 */
	uint64_t MaxInteger();
	/**
	 * 设置最大数值
	 * @param num 
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void SetMaxInteger(uint64_t num, bool auto_adjust = true);
	/**
	 * 最小数值
	 */
	uint64_t MinInteger() const;
	/**
	 * 设置最小数值
	 * @param num
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void SetMinInteger(uint64_t num, bool auto_adjust = true);

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
