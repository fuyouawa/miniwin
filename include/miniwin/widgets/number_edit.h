#pragma once
#include <miniwin/widgets/text_edit.h>

namespace miniwin {
class NumberEdit : public TextEdit {
	MW_OBJECT
public:
	NumberEdit();
	~NumberEdit() override;

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
	uint64_t ToNumber() const;
	/**
	 * 设置数字，内部会根据进制自动转换为对应的文本
	 * @param num 
	 */
	void SetNumber(uint64_t num);

	/**
	 * 是否启动了数值限制
	 */
	bool HasNumberLimit() const;
	/**
	 * 启动数值限制
	 * @param b 
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void EnableNumberLimit(bool b, bool auto_adjust = true);
	/**
	 * 最大数值
	 */
	uint64_t MaxNumber();
	/**
	 * 设置最大数值
	 * @param num 
	 * @param auto_adjust 如果为true，会自动调用AdjustNumber
	 */
	void SetMaxNumber(uint64_t num, bool auto_adjust = true);

	/**
	 * 调整数值，如果启动了NumberLimit，则确保在MaxNumber范围内
	 */
	void AdjustNumber();

protected:
	wchar_t FilterInputChar(const FilterInputCharArgs& args) override;

	_MW_IMPL
};
}
