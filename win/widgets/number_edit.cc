#include <miniwin/widgets/number_edit.h>

#include "win/tools/debug.h"

namespace miniwin {
class NumberEdit::Impl {
public:
	Impl() = default;

	uint8_t base = 10;
	bool num_limit = true;
	uint64_t max_num_ = std::numeric_limits<uint64_t>::max();
};

NumberEdit::NumberEdit() {
	impl_ = std::make_unique<Impl>();
}

NumberEdit::~NumberEdit() {}

uint8_t NumberEdit::Base() const {
	return impl_->base;
}

void NumberEdit::SetBase(uint8_t base) {
	if (!(base == 2 || base == 8 || base == 10 || base == 16)) {
		MW_THROW_EX(std::invalid_argument, "Illegal 'base' = {}, must be 2 or 8 or 10 or 16", base);
	}
	impl_->base = base;
}

uint64_t NumberEdit::ToNumber() const {
	auto str = PlainText();
	return str.ToNumber(Base());
}

void NumberEdit::SetNumber(uint64_t num) {
	SetPlainText(String::FromNumber(num, Base()));
}

bool NumberEdit::HasNumberLimit() const {
	return impl_->num_limit;
}

void NumberEdit::EnableNumberLimit(bool b, bool auto_adjust) {
	impl_->num_limit = b;
	if (b && auto_adjust) {
		AdjustNumber();
	}
}

uint64_t NumberEdit::MaxNumber() {
	return impl_->max_num_;
}

void NumberEdit::SetMaxNumber(uint64_t num, bool auto_adjust) {
	impl_->max_num_ = num;
	if (auto_adjust) {
		AdjustNumber();
	}
}

void NumberEdit::AdjustNumber() {
	if (!HasNumberLimit())
		return;

	try {
		auto num = ToNumber();
		if (num > MaxNumber()) {
			SetNumber(MaxNumber());
		}
	}
	catch (const std::out_of_range&) {
		SetNumber(MaxNumber());
	}
}

wchar_t NumberEdit::FilterInputChar(const FilterInputCharArgs& args) {
	auto ch = TextEdit::FilterInputChar(args);
	if (!ch)
		return 0;

	if (!IsNumber(ch, Base())) {
		return 0;
	}

	if (HasNumberLimit()) {
		auto n = (PlainText() + static_cast<char>(args.input_char)).ToNumber(Base());
		if (n > MaxNumber()) {
			return 0;
		}
	}

	return ch;
}
}
