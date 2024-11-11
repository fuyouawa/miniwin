#pragma once

namespace miniwin {
enum class KeyCode
{
	kCtrl
};

namespace io {
bool IsKeyDown(KeyCode kc);
}
}
