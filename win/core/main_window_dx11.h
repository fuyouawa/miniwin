#pragma once
#include "main_window_impl.h"

namespace miniwin {
class PlatformEasyWindowDx11;
}

namespace miniwin {
class MainWindowDx11 : public MainWindowImpl {
public:
	MainWindowDx11(
		const String& title,
		const Vector2DInt& size,
		bool adjust_size,
		FlagsType styles,
		const SharedMainWindow& parent);
	~MainWindowDx11() override;

	void Initialize() override;
	void PlatformStartFrame() override;
	void PlatformAdditionRender() override;
	void PlatformPreRender() override;

	PlatformEasyWindowDx11* platform_win_dx11_;
};
}
