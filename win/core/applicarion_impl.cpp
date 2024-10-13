#include "win/core/applicarion_impl.h"
#include "win/core/widgets_driver.h"

#include "imgui/backends/imgui_impl_opengl3.h"

#include <cassert>
#include <thread>

namespace miniwin {
Application::Impl::Impl(Application* owner)
    : close_in_next_frame_(false), is_executing_(false), delta_time_(0), cur_scale_(), prev_scale_(), owner_(owner)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void Application::Impl::OnAppStart()
{
    is_executing_ = true;
}

void Application::Impl::OnProcess()
{
    WidgetsDriver::instance().Update();
    if (close_in_next_frame_)
    {
        assert(IsDone());
    }
}

bool Application::Impl::IsDone()
{
    return WidgetsDriver::instance().IsDone();
}

void Application::Impl::OnDpiScaleChanged()
{
    auto& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 16 * cur_scale_.x, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->Build();
    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_CreateFontsTexture();
}

void Application::Impl::OnAppExit()
{
    is_executing_ = false;
}

void Application::Impl::WindowWannaClose()
{
    WidgetsDriver::instance().CloseAll();
    close_in_next_frame_ = true;
}

void Application::Impl::DoFps() const
{
    auto sleep_time = 1000 / fps_;
    if (sleep_time > delta_time_) {
        std::this_thread::sleep_for(std::chrono::milliseconds{ sleep_time - delta_time_ });
    }
}
}

