#pragma once

namespace miniwin {
enum class IoKeyCode
{
	kCtrl
};

enum class KeyCode
{
	//TODO KeyCode
};

class Input
{
public:
	static bool IsIoKeyDown(IoKeyCode kc);
};
}
