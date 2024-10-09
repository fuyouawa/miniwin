cmake_minimum_required(VERSION 3.5...3.21 FATAL_ERROR)
project(fugui_example)

set(CMAKE_CXX_STANDARD 20)

include_directories(${HEAD_PATH})

set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
add_executable(fugui_example main.cpp)

link_directories(${LIB_PATH})
target_link_libraries(fugui_example ${FUGUI_LIB})