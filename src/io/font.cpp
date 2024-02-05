#include <mvcgui/io/font.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace mvcgui {
void FontUtil::Clear() {
	ImGui::GetIO().Fonts->Clear();
}

Font FontUtil::AddFont(std::string_view filename, float pixel, FontGlyphAssert assert, const FontConfig& config) {
	auto& io = ImGui::GetIO();
	const ImWchar* ranges = nullptr;
	switch (assert)
	{
	case mvcgui::FontGlyphAssert::kChineseFull:
		ranges = io.Fonts->GetGlyphRangesChineseFull();
		break;
	case mvcgui::FontGlyphAssert::kChineseSimplified2500:
		ranges = io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
		break;
	case mvcgui::FontGlyphAssert::kChineseSimplified7000:
		//TODO kChineseSimplified7000
		break;
	default:
		break;
	}
	assert(ranges);
	ImFontConfig cfg{};
	auto font = io.Fonts->AddFontFromFileTTF(filename.data(), pixel, &cfg, ranges);
	return {};
}

void FontUtil::Rebuild()
{
	ImGui::GetIO().Fonts->Build();
	ImGui_ImplOpenGL3_DestroyFontsTexture();
	ImGui_ImplOpenGL3_CreateFontsTexture();
}
}