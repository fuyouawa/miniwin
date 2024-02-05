#pragma once
#include <string_view>

namespace mvcgui {
class Font {
public:

};

struct FontConfig {
	//TODO FontConfig
};

enum class FontGlyphAssert
{
	kChineseFull,
	kChineseSimplified2500,
	kChineseSimplified7000
};

class FontUtil
{
public:
	static void Clear();
	static Font AddFont(
		std::string_view filename,
		float pixel,
		FontGlyphAssert assert = FontGlyphAssert::kChineseFull,
		const FontConfig& config = FontConfig{});
	static void Rebuild();
};
}