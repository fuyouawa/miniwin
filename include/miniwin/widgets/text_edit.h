#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class TextEdit : public AbstractMinimumControl {
	MW_OBJECT
public:
	struct FilterInputCharArgs {
		wchar_t input_char;
		size_t cur_length;
	};

	TextEdit();
	~TextEdit() override;

	const String& RightLabel() const;
	void SetRightLabel(const String& label);

	void SetPlainText(const String& text);
	const String& PlainText() const;

	size_t MaxLength() const;
	void SetMaxLength(size_t len);

	MW_SIGNAL(OnTextChanged)

protected:
	void Awake() override;

	virtual wchar_t FilterInputChar(const FilterInputCharArgs& args);

	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
