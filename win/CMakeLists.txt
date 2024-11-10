cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(miniwin)

set(CMAKE_CXX_STANDARD 20)

include_directories(${HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH}/imgui)
include_directories(${GUI_HEAD_PATH})

# 根据平台加入ImGui的后端源文件
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
set(IMGUI_SRC
	${IMGUI_SRC_PATH}/backends/imgui_impl_win32.cpp
	${IMGUI_SRC_PATH}/backends/imgui_impl_dx11.cpp
)
else()
include_directories(${GLFW_HEAD_PATH})
set(IMGUI_SRC
	${IMGUI_SRC_PATH}/backends/imgui_impl_opengl3.cpp
	${IMGUI_SRC_PATH}/backends/imgui_impl_glfw.cpp
)
endif()

# 加入ImGui的源文件
aux_source_directory(${IMGUI_SRC_PATH} IMGUI_SRC)
aux_source_directory(${IMGUI_SRC_PATH}/misc/cpp IMGUI_SRC)

aux_source_directory(./tools SRC)
aux_source_directory(./core SRC)
aux_source_directory(./widgets SRC)
aux_source_directory(./widgets/layout SRC)
aux_source_directory(./widgets/view SRC)
aux_source_directory(./widgets/base SRC)
aux_source_directory(./delegate SRC)
aux_source_directory(./delegate/base SRC)
aux_source_directory(./io SRC)
aux_source_directory(./model SRC)
aux_source_directory(./model/base SRC)

add_library(${MINIWIN_LIB} STATIC ${SRC} ${IMGUI_SRC})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#TODO Windows平台
else()
target_link_libraries(${MINIWIN_LIB} PRIVATE ${GLFW_LIB})
endif ()

include(GNUInstallDirs)

# 安装库
install(TARGETS ${MINIWIN_LIB}
        EXPORT miniwinTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})


# 安装导出文件
install(EXPORT miniwinTargets
        FILE miniwinTargets.cmake
        NAMESPACE miniwin::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/miniwin)

# 安装配置文件
configure_file(miniwinConfig.cmake.in
               "${CMAKE_CURRENT_BINARY_DIR}/miniwinConfig.cmake" @ONLY)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/miniwinConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/miniwinConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/miniwin)

# 版本文件
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/miniwinConfigVersion.cmake"
"set(miniwin_VERSION 1.0.0)\n"
"set(miniwin_VERSION_MAJOR 1)\n"
"set(miniwin_VERSION_MINOR 0)\n"
"set(miniwin_VERSION_PATCH 0)\n")