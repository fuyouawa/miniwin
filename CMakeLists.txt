cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(miniwin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(MINIWIN_LIB miniwin_d)
else()
set(MINIWIN_LIB miniwin)
endif()

set(GUI_HEAD_PATH ${PROJECT_SOURCE_DIR})
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)
set(IMGUI_HEAD_PATH ${THIRD_PARTY_DIR})
set(IMGUI_SRC_PATH ${THIRD_PARTY_DIR}/imgui)
set(GLFW_HEAD_PATH ${THIRD_PARTY_DIR}/glfw/include)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
else()
set(GLFW_LIB glfw)
add_subdirectory(${THIRD_PARTY_DIR}/glfw)
endif()

# 针对不同的编译器设置 UTF-8 编译选项
if (MSVC)
    add_compile_options("/utf-8")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options("-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()

add_subdirectory(win)
add_subdirectory(example)
