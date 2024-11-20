#pragma once
#include <miniwin/widgets/base/abstract_control.h>

namespace miniwin {
class TextEdit : public AbstractMinimumControl {
	MW_OBJECT
public:
	TextEdit();
	~TextEdit() override;

	const String& RightLabel() const;
	void SetRightLabel(const String& label);

	void SetPlainText(const String& text);
	const String& PlainText() const;

	MW_SIGNAL(OnTextChanged)

protected:
	void Awake() override;

	virtual wchar_t OnFilterInputChar(wchar_t ch);

	void PaintBegin(size_t index) override;

	_MW_IMPL
};
}
