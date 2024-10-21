cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(miniwin)

set(CMAKE_CXX_STANDARD 20)

include_directories(${HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH})
include_directories(${IMGUI_HEAD_PATH}/imgui)
include_directories(${GUI_HEAD_PATH})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#TODO Windows平台
else()
include_directories(${GLFW_HEAD_PATH})
endif ()

aux_source_directory(./tools SRC)
aux_source_directory(./core SRC)
aux_source_directory(./widgets SRC)
aux_source_directory(./widgets/view SRC)
aux_source_directory(./widgets/base SRC)
aux_source_directory(./delegate SRC)
aux_source_directory(./delegate/base SRC)
aux_source_directory(./io SRC)
aux_source_directory(./model SRC)
aux_source_directory(./model/base SRC)

add_library(${MINIWIN_LIB} STATIC ${SRC})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#TODO Windows平台
else()
target_link_libraries(${MINIWIN_LIB} PRIVATE ${GLFW_LIB})
endif ()
