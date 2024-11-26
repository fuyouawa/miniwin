#pragma once
#include "platform_window_impl.h"

namespace miniwin {
class PlatformEasyWindowDx11;
}

namespace miniwin {
class PlatformWindowDx11 : public PlatformWindowImpl {
public:
	PlatformWindowDx11(
		const String& title,
		const Vector2DInt& size,
		bool adjust_size,
		FlagsType styles,
		const SharedPlatformWindow& parent);
	~PlatformWindowDx11() override;

	void Initialize() override;
	void PlatformStartFrame() override;
	void PlatformAdditionRender() override;
	void PlatformPreRender() override;

	PlatformEasyWindowDx11* platform_win_dx11_;
};
}
