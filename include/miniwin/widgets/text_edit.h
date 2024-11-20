#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class TextEdit : public AbstractMinimumControl {
	MW_OBJECT
public:
	struct FilterInputArgs {
		wchar_t input_char;
		KeyCode input_key;
		size_t cur_length;
	};

	TextEdit();
	~TextEdit() override;

	String RightLabel() const;
	void SetRightLabel(const String& label);

	void SetTextBuffer(const String& text);
	const String& TextBuffer() const;
	String& TextBuffer();

	size_t MaxLength() const;
	void SetMaxLength(size_t len);

	MW_SIGNAL(OnTextChanged)

protected:
	void Awake() override;

	virtual bool FilterInput(FilterInputArgs& args);

	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
