#pragma once

namespace mvcgui {
enum class KeyCode
{
	kCtrl
};

class Input
{
public:
	static bool GetKeyDown(KeyCode kc);
};
}