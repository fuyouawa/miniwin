cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(FUGUI_LIB)

set(CMAKE_CXX_STANDARD 20)

include_directories(${HEAD_PATH})
include_directories(${HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH}/imgui)
include_directories(${GLFW_HEAD_PATH})
include_directories(${GUI_HEAD_PATH})

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(${FUGUI_LIB} STATIC ${SRC})

target_link_libraries(${FUGUI_LIB} PRIVATE ${GLFW_LIB})