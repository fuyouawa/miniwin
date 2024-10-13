cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(MINIWIN_LIB)

set(CMAKE_CXX_STANDARD 20)

include_directories(${HEAD_PATH})
include_directories(${HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH}/imgui)
include_directories(${GLFW_HEAD_PATH})
include_directories(${GUI_HEAD_PATH})

aux_source_directory(./tools SRC)
aux_source_directory(./core SRC)
aux_source_directory(./widgets SRC)
aux_source_directory(./widgets/base SRC)

add_library(${MINIWIN_LIB} STATIC ${SRC})

target_link_libraries(${MINIWIN_LIB} PRIVATE ${GLFW_LIB})
