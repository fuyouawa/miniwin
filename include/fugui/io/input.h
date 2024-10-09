#pragma once

namespace fugui {
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