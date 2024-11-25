#pragma once
#include <cstdint>
#include <memory>

namespace miniwin {
using FlagsType = int32_t;
using WidgetId = uint16_t;

enum class KeyCode : uint32_t
{    // Keyboard
    kNone = 0,
    kTab = 512,             // == kNamedKey_BEGIN
    kLeftArrow,
    kRightArrow,
    kUpArrow,
    kDownArrow,
    kPageUp,
    kPageDown,
    kHome,
    kEnd,
    kInsert,
    kDelete,
    kBackspace,
    kSpace,
    kEnter,
    kEscape,
    kLeftCtrl, kLeftShift, kLeftAlt, kLeftSuper,
    kRightCtrl, kRightShift, kRightAlt, kRightSuper,
    kMenu,
    k0, k1, k2, k3, k4, k5, k6, k7, k8, k9,
    kA, kB, kC, kD, kE, kF, kG, kH, kI, kJ,
    kK, kL, kM, kN, kO, kP, kQ, kR, kS, kT,
    kU, kV, kW, kX, kY, kZ,
    kF1, kF2, kF3, kF4, kF5, kF6,
    kF7, kF8, kF9, kF10, kF11, kF12,
    kF13, kF14, kF15, kF16, kF17, kF18,
    kF19, kF20, kF21, kF22, kF23, kF24,
    kApostrophe,        // '
    kComma,             // ,
    kMinus,             // -
    kPeriod,            // .
    kSlash,             // /
    kSemicolon,         // ;
    kEqual,             // =
    kLeftBracket,       // [
    kBackslash,         // \ (this text inhibit multiline comment caused by backslash)
    kRightBracket,      // ]
    kGraveAccent,       // `
    kCapsLock,
    kScrollLock,
    kNumLock,
    kPrintScreen,
    kPause,
    kKeypad0, kKeypad1, kKeypad2, kKeypad3, kKeypad4,
    kKeypad5, kKeypad6, kKeypad7, kKeypad8, kKeypad9,
    kKeypadDecimal,
    kKeypadDivide,
    kKeypadMultiply,
    kKeypadSubtract,
    kKeypadAdd,
    kKeypadEnter,
    kKeypadEqual,
    kAppBack,               // Available on some keyboard/mouses. Often referred as "Browser Back"
    kAppForward,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    kGamepadStart,          // Menu (Xbox)      + (Switch)   Start/Options (PS)
    kGamepadBack,           // View (Xbox)      - (Switch)   Share (PS)
    kGamepadFaceLeft,       // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    kGamepadFaceRight,      // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    kGamepadFaceUp,         // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    kGamepadFaceDown,       // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    kGamepadDpadLeft,       // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    kGamepadDpadRight,      // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    kGamepadDpadUp,         // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    kGamepadDpadDown,       // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    kGamepadL1,             // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    kGamepadR1,             // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    kGamepadL2,             // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    kGamepadR2,             // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    kGamepadL3,             // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    kGamepadR3,             // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    kGamepadLStickLeft,     // [Analog]                                         // Move Window (in Windowing mode)
    kGamepadLStickRight,    // [Analog]                                         // Move Window (in Windowing mode)
    kGamepadLStickUp,       // [Analog]                                         // Move Window (in Windowing mode)
    kGamepadLStickDown,     // [Analog]                                         // Move Window (in Windowing mode)
    kGamepadRStickLeft,     // [Analog]
    kGamepadRStickRight,    // [Analog]
    kGamepadRStickUp,       // [Analog]
    kGamepadRStickDown,     // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    kMouseLeft, kMouseRight, kMouseMiddle, kMouseX1, kMouseX2, kMouseWheelX, kMouseWheelY,
};

enum class IoKeyCode : uint8_t {
    kNone,
	kCtrl,
    kAlt,
    kShift,
    kSuper
};

enum class MouseButton : uint8_t {
	kLeft,
    kRight,
    kMiddle
};

enum class HeaderOrientation : uint8_t {
    kHorizontal,
    kVertical
};

enum class ItemRole : uint8_t {
    kDisplay,
    kUserData,
    kFlags
};

enum class Alignment : uint8_t {
    kNone,
	kLeft,
    kRight,
    kTop,
    kBottom,
    kCenter
};

enum class WindowRelativeTo : uint8_t {
    kMainWindow,
    kScene
};
}

#define _MW_IMPL                    \
private:                            \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;

#define _MW_PUB_IMPL                \
public:                             \
    class Impl;                     \
    std::unique_ptr<Impl> impl_;