cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(miniwin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(MINIWIN_LIB miniwin)
set(GLFW_LIB glfw)

set(GUI_HEAD_PATH ${PROJECT_SOURCE_DIR})
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)
set(IMGUI_HEAD_PATH ${THIRD_PARTY_DIR})
set(GLFW_HEAD_PATH ${THIRD_PARTY_DIR}/glfw/include)

add_subdirectory(win)
add_subdirectory(example)


add_subdirectory(${THIRD_PARTY_DIR}/glfw)
