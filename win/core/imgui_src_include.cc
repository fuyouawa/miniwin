#pragma once

#include <imgui/imgui.cpp>
#include <imgui/imgui_draw.cpp>
#include <imgui/imgui_tables.cpp>
#include <imgui/imgui_widgets.cpp>

#if WIN32
#include <imgui/backends/imgui_impl_win32.cpp>
#include <imgui/backends/imgui_impl_dx11.cpp>
#else
#include <imgui/backends/imgui_impl_opengl3.cpp>
#include <imgui/backends/imgui_impl_glfw.cpp>
#endif // WIN32
