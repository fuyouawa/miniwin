#include <miniwin/widgets/Integer_edit.h>

#include "win/tools/debug.h"

namespace miniwin {
class IntegerEdit::Impl {
public:
	Impl() = default;

	uint8_t base_ = 10;
	bool limit_ = true;
	uint64_t max_int_ = std::numeric_limits<uint64_t>::max();
	uint64_t min_int_ = 0;
};

IntegerEdit::IntegerEdit() {
	impl_ = std::make_unique<Impl>();
}

IntegerEdit::~IntegerEdit() {}

uint8_t IntegerEdit::Base() const {
	return impl_->base_;
}

void IntegerEdit::SetBase(uint8_t base) {
	if (!(base == 2 || base == 8 || base == 10 || base == 16)) {
		MW_THROW_EX(std::invalid_argument, "Illegal 'base' = {}, must be 2 or 8 or 10 or 16", base);
	}
	impl_->base_ = base;
}

uint64_t IntegerEdit::ToUInteger() const {
	auto& str = TextBuffer();
	if (str.empty())
		return 0;
	return str.ToInteger(Base());
}

void IntegerEdit::SetUInteger(uint64_t val) {
	SetTextBuffer(String::FromInteger(val, Base()));
}

bool IntegerEdit::HasLimit() const {
	return impl_->limit_;
}

void IntegerEdit::EnableLimit(bool b, bool auto_adjust) {
	impl_->limit_ = b;
	if (b && auto_adjust) {
		AdjustInteger();
	}
}

uint64_t IntegerEdit::MaxUInteger() {
	return impl_->max_int_;
}

void IntegerEdit::SetMaxUInteger(uint64_t num, bool auto_adjust) {
	impl_->max_int_ = num;
	if (auto_adjust) {
		AdjustInteger();
	}
}

uint64_t IntegerEdit::MinUInteger() const {
	return impl_->min_int_;
}

void IntegerEdit::SetMinUInteger(uint64_t num, bool auto_adjust) {
	impl_->min_int_ = num;
	if (auto_adjust) {
		AdjustInteger();
	}
}

void IntegerEdit::AdjustInteger() {
	if (!HasLimit())
		return;

	try {
		auto num = ToUInteger();
		if (num > MaxUInteger()) {
			SetUInteger(MaxUInteger());
		}
		else if (num < MinUInteger()) {
			SetUInteger(MinUInteger());
		}
	}
	catch (const std::out_of_range&) {
		SetUInteger(MaxUInteger());
	}
}

void IntegerEdit::Start() {
	TextEdit::Start();

	if (TextBuffer().empty()) {
		SetTextBuffer("0");
	}
	//TODO 最小数值的处理
	auto self = shared_from_this();
	Connect(self, &IntegerEdit::OnTextChanged, self, [this]() {
		AdjustInteger();
		});
}

void IntegerEdit::BeginUpdate(size_t index) {
	TextEdit::BeginUpdate(index);

	if (TextBuffer().empty()) {
		SetTextBuffer("0");
	}
}

bool IntegerEdit::FilterInput(FilterInputArgs& args) {
	if (!TextEdit::FilterInput(args))
		return false;

	if (args.input_char) {
		if (!IsNumber(args.input_char, Base())) {
			return false;
		}

		if (HasLimit()) {
			auto n = (TextBuffer() + static_cast<char>(args.input_char)).ToInteger(Base());
			if (n > MaxUInteger()) {
				return false;
			}
		}
	}

	return true;
}
}
